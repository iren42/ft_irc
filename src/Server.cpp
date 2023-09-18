#include "Server.hpp"

// test iren
Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}


Server::Server(std::string port, std::string pw) : _port(port), _pw(pw)
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

	if ((_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("Error while generating socket\n");

	if (fcntl(_sockfd, F_SETFL, O_NONBLOCK) < 0)
		throw std::runtime_error("Error while setting socket to non blocking mode\n");

	struct sockaddr_in serv_socket = {AF_INET, 0, {0}, {0}};
	serv_socket.sin_addr.s_addr = htonl(INADDR_ANY);
	int port = std::strtol(_port.c_str(), NULL, 10);
std::cout << "char port = '" << _port << "', int port = '" << port << "'\n";
	if (port <= 0 || port > 65535)
		throw std::invalid_argument("Invalid port number\n");
	serv_socket.sin_port = htons(port);

	if (bind(_sockfd, (struct sockaddr*) & serv_socket, sizeof(serv_socket)) < 0)
		throw std::runtime_error("Error while binding socket\n");

	if (listen(_sockfd, 1000) < 0)
		throw std::runtime_error("Error while listening on socket\n");

	std::cout << "Server socket has been generated\n";
}
