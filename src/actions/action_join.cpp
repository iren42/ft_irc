#include "Server.hpp"

void Server::do_action_join(Client *client, std::vector<std::string> args) {

    if (args.size() < 2) {
        client->send_msg(BOLDRED + "Erreur: Format : JOIN <nom du canal> [mot de passe] " + RESET);
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "JOIN"));
        return;
    }


    if (args[1][0] != '#') {
        client->send_msg(BOLDRED + "Erreur: Le nom du canal doit commencer par # " + RESET);
        client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), args[1]));
        return;
    }


    std::string canal_name = args[1];

    CHANNELS::iterator it = _map_channel.find(canal_name);

    if (it != _map_channel.end()) {
        Channel *channel = it->second;

        if (channel->getLockPass() != "") {
            if (args.size() != 3) {
                client->send_msg(BOLDRED + "Le channel " + canal_name + " a un mot de passe." + RESET);
				client->reply(ERR_BADCHANNELKEY(client->getNickname(), canal_name));
                return;
            }
            std::string mdp = args[2];
            if (mdp != channel->getLockPass()) {
                client->reply(ERR_BADCHANNELKEY(client->getNickname(), canal_name));
                client->send_msg(BOLDRED + "Mauvais mot de passe." + RESET);
                std::cout << "real mdp : " << channel->getLockPass() << std::endl;
                std::cout << "given mdp : " << mdp << std::endl;
                return;
            }
        }

        if (channel->is_client(client))
        {
            client->send_msg("Vous êtes déjà dans ce canal");
            return;
        }
        else {
            if (channel->add_client(client)) {
                client->send_msg("Vous venez de rejoindre le canal " + args[1]);

            } else {
                client->send_msg("Vous n'avez pas le droit de rejoindre ce canal");
                return;
            }
        }
    } else {
        Channel *new_Chanel = new Channel(canal_name, client);
        _map_channel[canal_name] = new_Chanel;

        client->send_msg("Vous venez de créer et de rejoindre le canal " + args[1]);
    }

    Channel *channel = get_channel_by_name(canal_name);

    std::string users;
    for (std::vector<Client *>::const_iterator it = channel->getClients().begin();
         it != channel->getClients().end(); ++it) {
        if (channel->is_op(*it))
            users += "@";
        users += (*it)->getNickname() + " ";
    }
    client->reply(RPL_NAMREPLY(client->getNickname(), channel->getName(), users));
    client->reply(RPL_ENDOFNAMES(client->getNickname(), channel->getName()));

    if (channel->getTopic() == "")
        client->reply(RPL_NOTOPIC(client->getNickname(), channel->getName()));
    else
        client->reply(RPL_TOPIC( channel->getName(), channel->getTopic()));

    channel->replyAll(client->getPrefix() + " " + RPL_JOIN(channel->getName()));
}
