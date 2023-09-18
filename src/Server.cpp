#include "Server.hpp"


Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}


Server::Server(int port, std::string pw) : _port(port), _pw(pw)
{
	std::cout << "Server constructor called" << std::endl;
	generate_socket();
}

void	Server::launch()
{
	int	fd;
	struct epoll_event	event;

	// create epoll object
	_epollfd = epoll_create1(0);
	if (_epollfd == -1)
		return ;
	event.data.fd = _epollfd; /* return the fd to us later */
	event.events = EPOLLIN;


	struct epoll_event *events ;
	int nr_events, i, epfd;

	// allocate events memory
	events = (struct epoll_event*)malloc (sizeof (*events) * MAX_EVENTS);
	if (!events) {
		std::cerr << "malloc" << std::endl;
		return ;
	}

	// block until an event occurs
	nr_events = epoll_wait (_epollfd, events, MAX_EVENTS, -1);
	if (nr_events < 0) {
		perror ("epoll_wait");
		free (events);
		return ;
	}

	// handle events
	for (i = 0; i < nr_events; i++) {
		printf ("event=%ld on fd=%dn",
				events[i].events,
				events[i].data.fd);
	}
}
void	Server::generate_socket()
{
	struct sockaddr_in sock_serv;
	/*
	struct sockaddr_in {
    short sin_family;           // Famille d'adresses (AF_INET pour IPv4)
    unsigned short sin_port;    // Numéro de port en ordre octet réseau (big-endian)
    struct in_addr sin_addr;    // Adresse IP en format binaire
    char sin_zero[8];           // Remplissage pour alignement mémoire}; */

	//creation de la socket
	_sock_fd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET -> on utilise IPv4, SOCK_STREAM -> socket de type flux (TCP), 0 pour mettre le protocole par defaut (IPv4)
	if (_sock_fd == -1) {
		throw std::runtime_error("Error while generating a socket");}
	if (fcntl(_sock_fd, F_SETFL, O_NONBLOCK) < 0) { //fcntl fonction modifiant les attribut socket, F_SETFL pour set un mode, O_NONBLOCK pour definir le mode a set (non bloquant)
		throw std::runtime_error("Error while setting spcket to non-blocking mode");}

	//initialisation de la structure sockaddr_in pour definir les parametre de l'adresse du Serveur
	sock_serv.sin_family = AF_INET; //sock utilise IPv4
	sock_serv.sin_addr.s_addr = INADDR_ANY; //le serveur ecoutera sur toutes les interfaces reseauc disponibles
	sock_serv.sin_port = htons(_port); //on convertit le port en ordre octet réseau

	//liage de la socket à l'adresse et au port
	if (bind(_sock_fd, (struct sockaddr*) &_sock_fd, sizeof(_sock_fd)) == -1){
		throw std::runtime_error("Error While binding socket");} //bind() lie la socket a l'adresse et au port spécifié, msg si Erreur

	if (listen(_sock_fd, sock_serv.sin_port) < 0) {
		throw std::runtime_error("Error while putting the socket in listening mode");}

	std::cout << "Server socket has been generated\n";
}
