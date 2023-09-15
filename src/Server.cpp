#include "Server.hpp"

// test iren
Server::~Server()
{
	std::cout << "Server destructor called" << std::endl;
}


Server::Server(std::string port, std::string pw) : _port(port), _pw(pw)
{
	std::cout << "Server constructor called" << std::endl;
}

void	Server::launch()
{}
void	Server::generate_socket()
{}
