#include "Server.hpp"

void Server::do_action_nick(Client *client, std::vector<std::string> args) {
    std::cout << "action nick" << std::endl;

    if (args.size() != 2) {
        client->send_msg("Bad argument number. Format : NICK new_nickname");
    } else {
        client->setNickname(args[1]);
        std::string msg = "Nickname changed to ";
        msg.append(args[1]);
        client->send_msg(msg);
    }
}