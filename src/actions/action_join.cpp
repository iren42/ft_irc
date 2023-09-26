#include "Server.hpp"

void Server::do_action_join(Client *client, std::vector<std::string> args) {

    if (args.size() != 2) {
        client->send_msg("Bad argument number. Format : JOIN canal_name");
        return;
    }

    std::string canal_name = args[1];

    std::map<std::string, Channel *>::iterator it = _map_channel.find(canal_name);

    if (it != _map_channel.end()) {
        //Le channel existe.
        Channel *channel = it->second;

        if (channel->is_client(client))
            client->send_msg("Vous êtes déjà dans ce canal");
        else {
            client->send_msg("Vous venez de rejoindre le canal " + args[1]);
            channel->add_client(client);
        }
    } else {
        Channel *new_Chanel = new Channel(canal_name, client);
        _map_channel[canal_name] = new_Chanel;

        client->send_msg("Vous venez de créer et de rejoindre le canal " + args[1]);
    }
}