#ifndef SERVER_HPP
#define SERVER_HPP

class Server;

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string>

#include <cstdlib> // malloc
#include <cstdio> // printf
#include <cstring> // strncmp

#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <map>

#include <arpa/inet.h>
#include <errno.h>
#include <vector>
#include <signal.h>


#include "Client.hpp"

#define MAX_EVENTS 64
#define READ_SIZE 100


#define SUCCESS 1
extern int running;

class Server
{
private:
	int _sockfd;
	int _epollfd;
	int _port;

	std::string _msg;
	std::string _pw;
	int	_swtch; //0 = nv message, 1 =message en cours;
	std::map<std::string, void (Server::*)(Client *, std::vector<std::string>)> _map_cmd;
    std::map<int, Client*> _map_client;
	Server(const Server &);
	Server &operator=(const Server &);

	int epoll_add_fd(int, int, struct epoll_event &);
	int new_connection(struct epoll_event &);
	ssize_t ser_recv(struct epoll_event &);


	void init_map_action();
	void parse_action(std::string s, Client *pClient);

	void do_action_nick(Client *, std::vector<std::string>);
	void do_action_username(Client *, std::vector<std::string>);
	void do_action_join(Client *, std::vector<std::string>);
	void do_action_part(Client *, std::vector<std::string>);
	void do_action_msg(Client *, std::vector<std::string>);
	void do_action_help(Client *, std::vector<std::string>);
	void do_action_quit(Client *, std::vector<std::string>);
	void do_action_list(Client *, std::vector<std::string>);
	void do_action_whois(Client *, std::vector<std::string>);
	void do_action_me(Client *, std::vector<std::string>);
	void do_action_kick(Client *, std::vector<std::string>);
	void do_action_invite(Client *, std::vector<std::string>);
	void do_action_topic(Client *, std::vector<std::string>);
	void do_action_mode(Client *, std::vector<std::string>);

public:
	~Server();
	Server(int, std::string);

	void launch();
	void generate_socket();
	std::string handle_client(int client_fd);
};

#endif
