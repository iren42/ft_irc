#include "Server.hpp"

void Server::do_action_quit(Client *client, std::vector<std::string> args)
{
	(void) args;
	client->reply(RPL_QUIT);
	client->disconnect();
}