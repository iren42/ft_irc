#include "Server.hpp"

void Server::do_action_join(Client *client, std::vector<std::string> args) {

    if (args.size() != 2) {
        client->send_msg("Erreur: Format : JOIN <nom du canal> [mot de passe] ");
        return;
    }

    std::string canal_name = args[1];

    std::map<std::string, Channel *>::iterator it = _map_channel.find(canal_name);

    if (it != _map_channel.end()) {
        //Le channel existe.
        Channel *channel = it->second;

        if (channel->getLockPass() != "") {
            if (args.size() != 3)
                client->send_msg("\033[1;31mLe channel " + canal_name + " a un mot de passe.\033[0m");
            std::string mdp = args[3];
            if (mdp != channel->getLockPass())
                client->send_msg("\033[1;31mMauvais mot de passe.\033[0m");
        }

        if (channel->is_client(client))
            client->send_msg("Vous êtes déjà dans ce canal");
        else {
            if (channel->add_client(client))
                client->send_msg("Vous venez de rejoindre le canal " + args[1]);
            else
                client->send_msg("Vous n'avez pas le droit de rejoindre ce canal");
        }
    } else {
        Channel *new_Chanel = new Channel(canal_name, client);
        _map_channel[canal_name] = new_Chanel;

        client->send_msg("Vous venez de créer et de rejoindre le canal " + args[1]);
    }
}