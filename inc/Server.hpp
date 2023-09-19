#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string>

#include <cstdlib> // malloc
#include <cstdio> // printf
#include <cstring> // strncmp

#include <unistd.h>
#include <fcntl.h>

#include <arpa/inet.h>

#include <cerrno>

#define MAX_EVENTS 64
#define READ_SIZE 10

#define SUCCESS 1
class Server 
{
	private:
	int	_sockfd;
	int	_epollfd;
	int	_running;
	std::string	_port;
	std::string	_pw;

	Server(const Server&);
	Server& operator=(const Server&);

	int	epoll_add_fd(int, int, struct epoll_event&);
	int	new_connection(struct epoll_event&);
	public:
	~Server();
	Server(std::string, std::string);

		void	launch();
		void	generate_socket();
};

#endif
