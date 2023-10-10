#include "Server.hpp"
#include "Client.hpp"
#include <netdb.h>

int running;

// test iren
Server::~Server()
{
	CLIENTS::iterator it = _map_client.begin();
	while (it != _map_client.end())
	{
		close(it->second->getFd());
		delete it->second;
		++it;
	}

	std::map<std::string, Channel *>::iterator it2 = _map_channel.begin();
	while (it2 != _map_channel.end())
	{
		delete it2->second;
		++it2;
	}
	std::cout << "Serveur fermé" << std::endl;
	close(_epollfd);
	close(_sockfd);

}

Server::Server(int port, std::string pass) : _port(port), _pass(pass)
{
	std::cout << "Construction du serveur" << std::endl;
	std::cout << HEADER_MSG << std::endl;
	init_map_action();
	running = 1;
}

const std::string &Server::getPass() const
{ return (_pass); }

CLIENTS Server::getClients() const
{ return (_map_client); }

CHANNELS Server::getChannels() const
{ return (_map_channel); }

int Server::epoll_add_fd(int fd, int event_type, struct epoll_event &event)
{
	memset(&event, 0, sizeof(event));
	event.data.fd = fd;
	event.events = event_type;
	return (epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &event));
}

int Server::new_connection(struct epoll_event &event)
{
	struct sockaddr in_addr = {AF_INET, {0, 0, 0}};
	socklen_t in_len = sizeof(in_addr);
	int infd;

	// create new socket fd from pending listening socket queue
	infd = accept(_sockfd, &in_addr, &in_len);
	if (infd == -1)
	{
		// if is EAGAIN or EWOULDBLOCK, no incoming connections are present to be
		// accepted.
		if (errno == EAGAIN)
		{
			// Erreur EAGAIN
			fprintf(stderr,
					"Erreur : Ressource temporairement non disponible (EAGAIN).\n");
			return -1;
		} else if (errno == EWOULDBLOCK)
		{
			// Erreur EWOULDBLOCK
			fprintf(stderr, "Erreur : Opération bloquerait (EWOULDBLOCK).\n");
			return -1;
		}
	}
	// mark new socket fd as non -blocking
	if (fcntl(infd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error(
				"Erreur lors de la configuration du socket en mode non-bloquant.");

	char hostname[128];
	int returngetname;
	if ((returngetname = getnameinfo((struct sockaddr *) &in_addr,
									 sizeof(in_addr), hostname, 100, NULL, 0,
									 NI_NUMERICSERV)) != 0)
	{
		std::cout << returngetname << std::endl;
		throw std::runtime_error(
				"Erreur lors de la récupération du nom d'hôte sur le nouveau client.");
	}

	Client *client = new Client(hostname, infd, this);
	client->send_msg(HEADER_MSG);
	client->send_msg(WELCOME_MSG);
	std::cout << "New client : " << hostname << " ; " << infd << std::endl;
	_map_client[infd] = client;

	int result = epoll_add_fd(infd, EPOLLIN, event);

	if (result)
		fprintf(stderr, "Erreur lors de l'appel à epoll_add_fd  : %s\n",
				strerror(errno));

	return result;
}

ssize_t Server::ser_recv(struct epoll_event &event)
{
	Client *client = _map_client[event.data.fd];
	std::string message = handle_client(event.data.fd, client);
	if (message.empty())
		return 0;

	std::istringstream messageStream(message);
	std::string line;

	while (getline(messageStream, line, '\n'))
	{
		// Exécutez le code pour chaque ligne
		if (!line.empty() && line[line.length() - 1] == '\r')
			line.erase(line.length() - 1);

		std::cout << "Client_FD[" << event.data.fd << "] wrote'" << line << "'"
				  << std::endl;
		parse_action(line, client);
	}

	return 0;
}

Client *Server::get_client_by_nickname(std::string nickname)
{
	CLIENTS::iterator it = _map_client.begin();
	while (it != _map_client.end())
	{
		if (it->second->getNickname() == nickname)
			return it->second;
		else
			++it;
	}
	return 0;
}

Channel *Server::get_channel_by_name(std::string name)
{
	CHANNELS::iterator it = _map_channel.find(name);

	if (it == _map_channel.end())
	{
		return 0;
	}

	return it->second;
}

void Server::send_all(std::string msg)
{
	CLIENTS::iterator it = _map_client.begin();
	while (it != _map_client.end())
	{
		it->second->send_brut(msg);
		++it;
	}
}

void Server::disconnect(Client *pClient)
{

	std::cout << "Client disconnect " << pClient->getNickname() << std::endl;
	CLIENTS::iterator it = _map_client.begin();
	while (it != _map_client.end())
	{
		if (it->second == pClient)
			_map_client.erase(it++);
		else
			++it;
	}

	std::map<std::string, Channel *>::iterator it2 = _map_channel.begin();
	while (it2 != _map_channel.end())
	{
		it2->second->remove_client(pClient);
		if (it2->second->isEmpty())
		{
			delete it2->second;
			_map_channel.erase(it2++);
		} else
			++it2;
	}

	int fd = pClient->getFd();
	epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, 0);
	close(fd);
	delete pClient;
}

void handleSig(int sigint)
{
	std::cout << std::endl << "Exit server..." << std::endl;
	if (sigint == SIGINT)
		running = false;
}

void Server::launch()
{
	struct epoll_event event;
	struct epoll_event *events;

	int event_count;
	int i;

	signal(SIGINT, &handleSig);
	generate_socket();

	_epollfd = epoll_create1(0);
	if (_epollfd == -1)
		return;
	if (epoll_add_fd(_sockfd, EPOLLIN, event) == -1)
	{
		std::cerr << "Failed to add file descriptor to epoll" << std::endl;
		close(_epollfd);
		return;
	}
	events = (struct epoll_event *) malloc(sizeof(*events) * MAX_EVENTS);
	if (!events)
	{
		std::cerr << "malloc" << std::endl;
		close(_epollfd);
		return;
	}

	while (running)
	{
		std::cout << "Polling for input..." << std::endl;
		event_count = epoll_wait(_epollfd, events, MAX_EVENTS, -1);
		if (event_count < 0)
		{
			std::cerr << "epoll_wait" << std::endl;
			break;
		}
		i = 0;
		while (i < event_count)
		{
			if (events[i].data.fd == _sockfd)
			{
				if (new_connection(event) == -1)
				{
					running = 0;
					break;
				}

				std::cout << "Client_FD[" << event.data.fd << "] connected"
						  << std::endl;
			} else // is a READ msg
			{
				if (ser_recv(events[i]) == -1)
				{
					running = 0;
					break;
				}
			}
			i++;
		}
	}
	free(events);
	if (close(_epollfd))
		std::cerr << "Failed to close epoll file descriptor" << std::endl;

	if (close(_sockfd))
		throw std::runtime_error("failed to close socket file descriptor");
}


void Server::generate_socket()
{
	struct sockaddr_in _sock_serv;
	/*
	struct sockaddr_in {
	short sin_family;           // Famille d'adresses (AF_INET pour IPv4)
	unsigned short sin_port;    // Numéro de port en ordre octet réseau
	(big-endian) struct in_addr sin_addr;    // Adresse IP en format binaire char
	sin_zero[8];           // Remplissage pour alignement mémoire}; */

	// creation de la socket
	_sockfd = socket(AF_INET, SOCK_STREAM,
					 0); // AF_INET -> on utilise IPv4, SOCK_STREAM -> socket de type
	// flux (TCP), 0 pour mettre le protocole par defaut (IPv4)
	if (_sockfd == -1)
	{
		throw std::runtime_error("Erreur lors de la génération du socket");
	}
	if (fcntl(_sockfd, F_SETFL, O_NONBLOCK) < 0)
	{ // fcntl fonction modifiant les attribut socket, F_SETFL pour set un
		// mode, O_NONBLOCK pour definir le mode a set (non bloquant)
		throw std::runtime_error(
				"Erreur lors de la configuration du socket en mode non-bloquant.");
	}

	// initialisation de la structure sockaddr_in pour definir les parametre de
	// l'adresse du Serveur
	_sock_serv.sin_family = AF_INET;         // sock utilise IPv4
	_sock_serv.sin_addr.s_addr = INADDR_ANY; // le serveur ecoutera sur toutes les
	// interfaces reseauc disponibles
	_sock_serv.sin_port = htons(
			_port); // on convertit le port en ordre octet réseau

	// liage de la socket à l'adresse et au port
	if (bind(_sockfd, (struct sockaddr *) &_sock_serv, sizeof(_sock_serv)) ==
		-1)
	{
		throw std::runtime_error("Erreur lors de la liaison du socket");
	} // bind() lie la socket a l'adresse et au port spécifié, msg si Erreur

	if (listen(_sockfd, _sock_serv.sin_port) < 0)
	{
		throw std::runtime_error(
				"Erreur lors de la mise en mode d'écoute du socket.");
	}

	std::cout << "Le socket serveur a été créé.\n";
}
