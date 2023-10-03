#include <sstream>
#include <string>
#include <iostream>
#include "Server.hpp"


void Server::do_action_list(Client *client, std::vector<std::string> args) {
    size_t mapChannelSize = _map_channel.size();

    std::stringstream ss;
    ss << "Liste des canaux [" << mapChannelSize << "]" << std::endl;;
    ss << "--------------------------------" << std::endl;;

    std::map<std::string, Channel *>::iterator it;
    for (it = _map_channel.begin(); it != _map_channel.end(); ++it) {
        const std::string &channelName = it->first;
        Channel *channel = it->second;

        ss << channelName << std::endl;
    }

    client->send_msg(ss.str());


}

