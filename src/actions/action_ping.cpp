#include <sstream>
#include <string>
#include <iostream>
#include "Server.hpp"


void Server::do_action_ping(Client *client, std::vector<std::string> args) {
    if (args.size() == 1)
        args.push_back("");

    client->reply(RPL_PING(args[1]));

}

