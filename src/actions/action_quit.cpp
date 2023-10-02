#include "Server.hpp"

void Server::do_action_quit(Client *client, std::vector<std::string> args) {

    client->send_msg("Bye Bye " + client->getNickname());
    client->disconnect();

}