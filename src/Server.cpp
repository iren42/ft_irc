#include "Server.hpp"

// test iren
Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}


Server::Server(std::string port, std::string pw) : _port(port), _pw(pw)
{
	std::cout << "Server constructor called" << std::endl;
	_running = 1;
}

void	Server::launch()
{
	int	fd;
	struct epoll_event	event;
	char read_buffer[READ_SIZE + 1];
	int	event_count;

	generate_socket();
	// create epoll object
	_epollfd = epoll_create1(0);
	if (_epollfd == -1)
		return ;
	event.data.fd = _sockfd; /* return the fd to us later */
	event.events = EPOLLIN; 


	struct epoll_event *events ;
	int nr_events, i;
	size_t bytes_read;

	struct sockaddr	in_addr;
	socklen_t	in_len;
	int	infd;
	// allocate events memory
	events = (struct epoll_event*)malloc (sizeof (*events) * MAX_EVENTS);
	if (!events) {
		std::cerr << "malloc" << std::endl;
		return ;
	}
	if(epoll_ctl(_epollfd, EPOLL_CTL_ADD, _sockfd, &event))
	{
		fprintf(stderr, "Failed to add file descriptor to epoll\n");
		close(_epollfd);
		return ;
	}
	while (_running)
	{
		printf("\nPolling for input...\n");
		event_count = epoll_wait(_epollfd, events, MAX_EVENTS, -1);
		if (event_count < 0)
		{
			perror ("epoll_wait");
			free (events);
			return ;
		}
		i = 0;
		printf("%d ready events, %d\n", event_count, _sockfd);
		while (i < event_count)
		{
			if (events[i].data.fd == _sockfd)
			{
				infd = accept (_sockfd, &in_addr, &in_len); // create new socket fd from pending listening socket queue
				if (infd == -1) // error
				{
					if ((errno == EAGAIN) ||(errno == EWOULDBLOCK)) {
						break; // We have processed all incoming connections.
					}
					else {
						perror ("accept");
						break;}
				}

				int flags = fcntl (infd, F_GETFL, 0); // mark new socket fd as non -blocking
				flags |= O_NONBLOCK;
				fcntl (infd, F_SETFL, flags);

				event.data.fd = infd;
				event.events = EPOLLIN;
				epoll_ctl (_epollfd, EPOLL_CTL_ADD, infd, &event);
				std::cout << "Client_FD[" << event.data.fd << "] connected" << std::endl;

			}
			else // is a Client msg
			{
				for (i = 0; i < event_count; i++)
				{
					printf("Reading file descriptor '%d' -- ", events[i].data.fd);
					bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
					printf("%zd bytes read.\n", bytes_read);
					read_buffer[bytes_read] = '\0';
					printf("Read '%s'\n", read_buffer);

					if(!strncmp(read_buffer, "stop\n", 5))
						_running = 0;
				}

				std::cout << "Here 3" << std::endl;
			}
			i++;
		}


	}

	if (close(_epollfd)) {
		fprintf(stderr, "Failed to close epoll file descriptor\n");
		return ;
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
