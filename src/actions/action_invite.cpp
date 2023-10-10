#include "Server.hpp"

void Server::do_action_invite(Client *client, std::vector<std::string> args) {
    if (args.size() < 3) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "INVITE"));
        client->send_msg("Erreur dans le nombre d'arguments. Format: INVITE user_name channel_name");
        return;
    }

    std::string user_name = args[1];
    std::string channel_name = args[2];

    Client *theClient = get_client_by_nickname(user_name);
    Channel *theChannel = get_channel_by_name(channel_name);

    if (!theChannel) {
        client->send_msg(BOLDRED + "Le canal " + channel_name + " n'existe pas." + RESET);
		client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), channel_name));
        return;
    }

    if (!theChannel->is_op(client)) {
		client->reply(ERR_CHANOPRIVSNEEDED(client->getNickname(), channel_name));
        client->send_msg(BOLDRED + "Vous n'etes pas op sur le canal " + channel_name + RESET);
        return;
    }

    if (!theClient) {
        client->send_msg(BOLDRED + "Le client " + user_name + " n'a pas été trouvé." + RESET);
		client->reply(ERR_NOSUCHNICK(client->getNickname(), user_name));
        return;
    }

    if (theChannel->is_client(theClient)) {
		client->reply(ERR_USERONCHANNEL(client->getNickname(), user_name, channel_name));
        client->send_msg(BOLDRED + user_name + " est déjà dans le canal " + channel_name + RESET);
        return;
    }

    theChannel->add_invite(theClient);
//    theChannel->add_client(theClient);
    client->send_msg("vous avez invité " + user_name + " à rejoindre le canal " + channel_name);
    theClient->send_msg("vous avez été invité à rejoindre le canal " + channel_name);
    client->reply(RPL_INVITING(client->getPrefix(), user_name, channel_name));
}
