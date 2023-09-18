#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <string>

#include <cstdlib> // malloc
#include <cstdio> // printf
#include <cstring> // strncmp

#include <unistd.h>
#include <fcntl.h>

#include <arpa/inet.h>

#define MAX_EVENTS 64
#define READ_SIZE 10

class Server
{
	private:
	int	_sock_fd;
	int	_epollfd;
	int	_port;
    int	_running;
	std::string	_pw;

	Server(const Server&);
	Server& operator=(const Server&);


	public:
	~Server();
	Server(int, std::string);

		void	launch();
		void	generate_socket();
};

#endif
