#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string>
#include <sys/type.h>

class Server 
{
	private:
	int	_sockfd;
	int	_epollfd;
	int	_port;
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
