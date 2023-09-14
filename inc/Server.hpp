#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string>

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
