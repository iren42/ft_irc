#include "Server.hpp"

void Server::do_action_join(Client *client, std::vector<std::string> args) {

    if (args.size() != 2) {
        client->send_msg(BOLDRED + "Erreur: Format : JOIN <nom du canal> [mot de passe] "+RESET);
        return;
    }


	if (args[1][0] != '#'){
		client->send_msg(BOLDRED + "Erreur: Le nom du canal doit commencer par # "+RESET);
		return;
	}


    std::string canal_name = args[1];

    CHANNELS::iterator it = _map_channel.find(canal_name);

    if (it != _map_channel.end()) {
        Channel *channel = it->second;

        if (channel->getLockPass() != "") {
            if (args.size() != 3)
                client->send_msg(BOLDRED + "Le channel " + canal_name + " a un mot de passe."+RESET);
            std::string mdp = args[3];
            if (mdp != channel->getLockPass())
                client->send_msg(BOLDRED + "Mauvais mot de passe."+RESET);
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