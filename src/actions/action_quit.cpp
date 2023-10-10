#include "Server.hpp"

void Server::do_action_quit(Client *client, std::vector<std::string> args) {
	(void) args;
    client->send_msg("Bye Bye " + client->getNickname());
    client->reply( RPL_QUIT);
    client->disconnect();
}