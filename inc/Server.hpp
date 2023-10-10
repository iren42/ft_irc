#ifndef SERVER_HPP
#define SERVER_HPP

class Server;
class Channel;

#include <iostream>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <cstdio>  // printf

#include <cstdlib> // malloc
#include <cstring> // strncmp
#include <algorithm>

#include <fcntl.h>
#include <map>
#include <unistd.h>
#include <arpa/inet.h>

#include <errno.h>
#include <signal.h>
#include <vector>

#include "replycode.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Colors.hpp"
#include "Header.hpp"

#define MAX_EVENTS 64
#define READ_SIZE 100

#define WELCOME_MSG                                                            \
  "Bonjour ! Quel est le mot de passe d'ircserv ? Veuillez utiliser la "       \
  "commande /PASS <mdp>"

extern int running;

typedef std::map<int, Client *> CLIENTS;
typedef std::map<std::string, Channel *> CHANNELS;

class Server
{
private:
	int _sockfd;
	int _epollfd;
	int _port;

	std::string _pass;
	std::map<std::string, void (Server::*)(Client *, std::vector<std::string>)>
			_map_cmd;
	CLIENTS _map_client;
	CHANNELS _map_channel;

	Server(const Server &);

	Server &operator=(const Server &);

	int epoll_add_fd(int, int, struct epoll_event &);

	int new_connection(struct epoll_event &);

	ssize_t ser_recv(struct epoll_event &);

	Client *get_client_by_nickname(std::string nickname);

	Channel *get_channel_by_name(std::string name);

	void init_map_action();

	void parse_action(std::string s, Client *pClient);

	void do_action_pass(Client *, std::vector<std::string>);

	void do_action_nick(Client *, std::vector<std::string>);

	void do_action_user(Client *, std::vector<std::string>);

	void do_action_join(Client *, std::vector<std::string>);

	void do_action_part(Client *, std::vector<std::string>);

	void do_action_privmsg(Client *, std::vector<std::string>);

	void do_action_help(Client *, std::vector<std::string>);

	void do_action_quit(Client *, std::vector<std::string>);

	void do_action_list(Client *, std::vector<std::string>);

	void do_action_ping(Client *, std::vector<std::string>);

	void do_action_whois(Client *, std::vector<std::string>);

	void do_action_names(Client *, std::vector<std::string>);

	void do_action_kick(Client *, std::vector<std::string>);

	void do_action_invite(Client *, std::vector<std::string>);

	void do_action_topic(Client *, std::vector<std::string>);

	void do_action_mode(Client *, std::vector<std::string>);

	void do_action_notice(Client *, std::vector<std::string>);

	void do_action_cap(Client *, std::vector<std::string>);

	void do_action_who(Client *, std::vector<std::string>);

	void msgChannel(Client *, std::string, std::vector<std::string>);

	void msgClient(Client *, std::string, std::vector<std::string>);

	void noticeChannel(Client *, std::string, std::vector<std::string>);

	void noticeClient(Client *, std::string, std::vector<std::string>);

	bool isInMapChannel(std::string);


	CLIENTS::iterator findClient(std::string);

	std::string createMsg(std::vector<std::string>);

	void
	do_action_mode_channel(Client *client, std::vector<std::string> vector1);

	void do_action_mode_channel_limit(Client *client, Channel *channel,
									  std::string cmd,
									  std::vector<std::string> args);

	void do_action_mode_channel_key(Client *client, Channel *channel,
									std::string cmd,
									std::vector<std::string> args);

public:
	~Server();

	Server(int, std::string);

	void launch();

	void generate_socket();

	void client_disconnect(Client *client);

	std::string handle_client(int client_fd, Client *client);

	CLIENTS getClients() const;

	CHANNELS getChannels() const;

	const std::string &getPass() const;

	void disconnect(Client *pClient);

	void send_all(std::string);

};

#endif
