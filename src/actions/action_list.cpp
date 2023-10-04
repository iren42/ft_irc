#include <sstream>
#include <string>
#include <iostream>
#include "Server.hpp"


void Server::do_action_list(Client *client, std::vector<std::string> args) {
    size_t mapChannelSize = _map_channel.size();
	(void) args;
    std::stringstream ss;
    ss << "Liste des canaux [" << mapChannelSize << "]" << std::endl;;
    ss << "--------------------------------" << std::endl;;

    CHANNELS::iterator it;
	for (it = _map_channel.begin(); it != _map_channel.end(); ++it)
		ss << it->first << std::endl;

	client->send_msg(ss.str());


}

