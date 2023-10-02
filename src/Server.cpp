#include <netdb.h>
#include "Server.hpp"
#include "Client.hpp"

int running;

// test iren
Server::~Server() {
    std::cout << "Server destructor called" << std::endl;
}


Server::Server(int port, std::string pw) : _port(port), _pw(pw) {
    std::cout << "Server constructor called" << std::endl;
    init_map_action();
    running = 1;
    _swtch = 0;
}

const std::string& Server::getPass() const
{
  return (_pass);
}

CLIENTS Server::getClients() const
{
	return (_map_client);
}

CHANNELS  Server::getChannels() const
{
  return (_map_channel);
}

int Server::epoll_add_fd(int fd, int event_type, struct epoll_event &event) {
    event.data.fd = fd;
    event.events = event_type;
    return (epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &event));
}

int Server::new_connection(struct epoll_event &event) {
    struct sockaddr in_addr;
    socklen_t in_len;
    int infd;
    int flags;

    // create new socket fd from pending listening socket queue
    infd = accept(_sockfd, &in_addr, &in_len);
    if (infd == -1) {
        // if is EAGAIN or EWOULDBLOCK, no incoming connections are present to be accepted.
        if (!((errno == EAGAIN) || (errno == EWOULDBLOCK)))
            return (-1);
    }
    // mark new socket fd as non -blocking
    flags = fcntl(infd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(infd, F_SETFL, flags);

    char hostname[128];
	int returngetname;
    if ((returngetname = getnameinfo((struct sockaddr *) &in_addr, sizeof(in_addr), hostname, 100, NULL, 0, NI_NUMERICSERV)) != 0){
		std::cout << returngetname << std::endl;
        throw std::runtime_error("Error while getting hostname on new client.");}

  Client *client = new Client(hostname, infd);
  client->send_msg("Bienvenue sur ircserver !\nVeuillez entrer le mot de passe du serveur"
      " avec la commande :\n/PASS <mot de passe>");
  std::cout << "New client : " << hostname << " ; " << infd << std::endl;
  _map_client[infd] = client;

    return (epoll_add_fd(infd, EPOLLIN, event));
}

ssize_t Server::ser_recv(struct epoll_event &event) {
        Client *client = _map_client[event.data.fd];
		std::string message = handle_client(event.data.fd, client);
		if (!message[0]){
			return (0);}
        parse_action(message, client);

        std::cout << "Client_FD[" << event.data.fd << "] wrote'" << message << "'" << std::endl;

        if (!strncmp(message.c_str(), "/QUIT\n", 6) ||
            !strncmp(message.c_str(), "/quit\n", 6)) {
            std::cout << "Client_FD[" << event.data.fd << "] left the server"
                      << std::endl;
            close(event.data.fd);
        }

	return 0;
}

void handleSig(int sigint) {
    std::cout << std::endl << "Exsiting server..." << std::endl;
    if (sigint == SIGINT)
        running = false;
}

void Server::launch() {
    struct epoll_event event;
    struct epoll_event *events;

    int event_count;
    int i;

    signal(SIGINT, &handleSig);
    generate_socket();

    _epollfd = epoll_create1(0);
    if (_epollfd == -1)
        return;
    if (epoll_add_fd(_sockfd, EPOLLIN, event) == -1) {
        std::cerr << "Failed to add file descriptor to epoll" << std::endl;
        close(_epollfd);
        return;
    }
    events = (struct epoll_event *) malloc(sizeof(*events) * MAX_EVENTS);
    if (!events) {
        std::cerr << "malloc" << std::endl;
        close(_epollfd);
        return;
    }
	_swtch = 0;
    while (running) {
        std::cout << "Polling for input..." << std::endl;
        event_count = epoll_wait(_epollfd, events, MAX_EVENTS, -1);
        if (event_count < 0) {
            std::cerr << "epoll_wait" << std::endl;
            break;
        }
        i = 0;
        while (i < event_count) {
            if (events[i].data.fd == _sockfd) {
                if (new_connection(event) == -1) {
                    running = 0;
                    break;
                }

                std::cout << "Client_FD[" << event.data.fd << "] connected"
                          << std::endl;
            } else // is a READ msg
            {
                if (ser_recv(events[i]) == -1) {
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

void Server::generate_socket() {
    struct sockaddr_in _sock_serv;
    /*
    struct sockaddr_in {
    short sin_family;           // Famille d'adresses (AF_INET pour IPv4)
    unsigned short sin_port;    // Numéro de port en ordre octet réseau (big-endian)
    struct in_addr sin_addr;    // Adresse IP en format binaire
    char sin_zero[8];           // Remplissage pour alignement mémoire}; */

    //creation de la socket
    _sockfd = socket(AF_INET, SOCK_STREAM,
                     0); // AF_INET -> on utilise IPv4, SOCK_STREAM -> socket de type flux (TCP), 0 pour mettre le protocole par defaut (IPv4)
    if (_sockfd == -1) {
        throw std::runtime_error("Error while generating a socket");
    }
    if (fcntl(_sockfd, F_SETFL, O_NONBLOCK) <
        0) { //fcntl fonction modifiant les attribut socket, F_SETFL pour set un mode, O_NONBLOCK pour definir le mode a set (non bloquant)
        throw std::runtime_error(
                "Error while setting spcket to non-blocking mode");
    }

    //initialisation de la structure sockaddr_in pour definir les parametre de l'adresse du Serveur
    _sock_serv.sin_family = AF_INET; //sock utilise IPv4
    _sock_serv.sin_addr.s_addr = INADDR_ANY; //le serveur ecoutera sur toutes les interfaces reseauc disponibles
    _sock_serv.sin_port = htons(
            _port); //on convertit le port en ordre octet réseau

    //liage de la socket à l'adresse et au port
    if (bind(_sockfd, (struct sockaddr *) &_sock_serv, sizeof(_sock_serv)) ==
        -1) {
        throw std::runtime_error("Error While binding socket");
    } //bind() lie la socket a l'adresse et au port spécifié, msg si Erreur

    if (listen(_sockfd, _sock_serv.sin_port) < 0) {
        throw std::runtime_error(
                "Error while putting the socket in listening mode");
    }

    std::cout << "Server socket has been generated\n";
}
