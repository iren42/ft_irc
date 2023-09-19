#include "Server.hpp"

Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}

Server::Server(std::string port, std::string pw) : _port(port), _pw(pw)
{
	std::cout << "Server constructor called" << std::endl;
	_running = 1;
}

int	Server::epoll_add_fd(int fd, int event_type, struct epoll_event &event)
{
	event.data.fd = fd;
	event.events = event_type;
	return (epoll_ctl (_epollfd, EPOLL_CTL_ADD, fd, &event));
}

int	Server::new_connection(struct epoll_event &event)
{
	struct sockaddr	in_addr;
	socklen_t		in_len;
	int				infd;
	int				flags;

	// create new socket fd from pending listening socket queue
	infd = accept (_sockfd, &in_addr, &in_len); 
	if (infd == -1)
	{
		// if is EAGAIN or EWOULDBLOCK, no incoming connections are present to be accepted.
		if (!((errno == EAGAIN) || (errno == EWOULDBLOCK)))
			return (-1);
	}
	// mark new socket fd as non -blocking
	flags = fcntl (infd, F_GETFL, 0); 
	flags |= O_NONBLOCK;
	fcntl (infd, F_SETFL, flags);
	return (epoll_add_fd(infd, EPOLLIN, event));
}

void	Server::launch()
{
	struct epoll_event	event;
	struct epoll_event *events ;
	char read_buffer[READ_SIZE + 1];
	ssize_t	bytes_read;
	int	event_count;
	int	i;

	generate_socket();
	_epollfd = epoll_create1(0);
	if (_epollfd == -1)
		return ;
	if (epoll_add_fd(0, EPOLLIN, event) == -1)
	{
		std::cerr << "Failed to add file descriptor to epoll" << std::endl;
		close(_epollfd);
		return ;
	}
	if (epoll_add_fd(_sockfd, EPOLLIN, event) == -1)
	{
		std::cerr << "Failed to add file descriptor to epoll" << std::endl;
		close(_epollfd);
		return ;
	}
	events = (struct epoll_event*)malloc (sizeof (*events) * MAX_EVENTS);
	if (!events) {
		std::cerr << "malloc" << std::endl;
		close(_epollfd);
		return ;
	}
	while (_running)
	{
		//	std::cout << "Polling for input..." << std::endl;
		event_count = epoll_wait(_epollfd, events, MAX_EVENTS, -1);
		if (event_count < 0)
		{
			std::cerr << "epoll_wait" << std::endl;
			break ;
		}
		i = 0;
		while (i < event_count)
		{
			if (events[i].data.fd == _sockfd)
			{
				if (new_connection(event) == -1)
					break ;
				std::cout << "Client_FD[" << event.data.fd << "] connected" << std::endl;
			}
			else // is a READ msg
			{
				bytes_read = recv(events[i].data.fd, read_buffer, READ_SIZE, MSG_DONTWAIT);
				if (bytes_read == -1)
				{
					// program is stuck here when recv from fd 0
						std::cout << errno << " errno" << std::endl;
						break ;
				}
				else
				{
					read_buffer[bytes_read] = '\0';
					std::cout << bytes_read << " bytes read" << std::endl;
					std::cout << "Client_FD[" << events[i].data.fd << "] wrote'" << read_buffer << "'" << std::endl;
					if(!strncmp(read_buffer, "/QUIT\n", 6) || !strncmp(read_buffer, "/quit\n", 6))
					{
						std::cout << "Client_FD[" << events[i].data.fd << "] left the server." << std::endl;
						close (events[i].data.fd);
					}
				}
			}
			i++;
		}
	}
	free(events);
	if (close(_epollfd)) {
		std::cerr << "Failed to close epoll file descriptor" << std::endl;
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
