#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string>

#include <cstdlib> // malloc
#include <cstdio> // printf

#include <unistd.h>
#include <fcntl.h>

#include <arpa/inet.h>

#define MAX_EVENTS 64

class Server 
{
	private:
	int	_sockfd;
	int	_epollfd;
	std::string	_port;
	std::string	_pw;

	Server(const Server&);
	Server& operator=(const Server&);


	public:
	~Server();
	Server(std::string, std::string);

		void	launch();
		void	generate_socket();
};

#endif
