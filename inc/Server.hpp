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
#include "Channel.hpp"

#define MAX_EVENTS 64
#define READ_SIZE 100


#define SUCCESS 1
extern int running;

typedef std::map<int, Client*> CLIENTS;
typedef std::map<std::string, Channel*> CHANNELS;

class Server
{
private:
	int _sockfd;
	int _epollfd;
	int _port;
    int	_swtch; //0 = nv message, 1 =message en cours;

    std::string _msg;
    std::string _pass;
    std::map<std::string, void (Server::*)(Client *, std::vector<std::string>)> _map_cmd;
    std::map<int, Client*> _map_client;
    std::map<std::string, Channel*> _map_channel;

	Server(const Server &);
	Server &operator=(const Server &);

	int epoll_add_fd(int, int, struct epoll_event &);
	int new_connection(struct epoll_event &);
	ssize_t ser_recv(struct epoll_event &);


	void init_map_action();
	void parse_action(std::string s, Client *pClient);

    void do_action_pass(Client *, std::vector<std::string>);
    void do_action_nick(Client *, std::vector<std::string>);
    void do_action_username(Client *, std::vector<std::string>);
    void do_action_join(Client *, std::vector<std::string>);
    void do_action_part(Client *, std::vector<std::string>);
    void do_action_privmsg(Client *, std::vector<std::string>);
    void do_action_help(Client *, std::vector<std::string>);
    void do_action_quit(Client *, std::vector<std::string>);
    void do_action_list(Client *, std::vector<std::string>);
    void do_action_whois(Client *, std::vector<std::string>);
    void do_action_me(Client *, std::vector<std::string>);
    void do_action_kick(Client *, std::vector<std::string>);
    void do_action_invite(Client *, std::vector<std::string>);
    void do_action_topic(Client *, std::vector<std::string>);
    void do_action_mode(Client *, std::vector<std::string>);

    void	msgChannel(Client *, std::string, std::vector<std::string>);
    void	msgClient(Client *, std::string, std::vector<std::string>);
    std::string parseChannel(std::string);
    bool  isInMapChannel(std::string);
    CLIENTS::iterator findClient(std::string);
    std::string createMsg(std::vector<std::string>);

  public:
    ~Server();
    Server(int, std::string);

	void launch();
	void generate_socket();
	void client_disconnect(Client *client);
	std::string handle_client(int client_fd, Client *client);
	std::map<int, Client*> getClients();
    CLIENTS getClients() const;
    CHANNELS  getChannels() const;
    const std::string& getPass() const;
};

#endif
