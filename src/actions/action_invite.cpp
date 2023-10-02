#include "Server.hpp"

void Server::do_action_invite(Client *client, std::vector<std::string> args) {
    if (args.size() != 3) {
        client->send_msg("Erreur dans le nombre d'arguments. Format: INVITE user_name channel_name");
        return;
    }

    std::string user_name = args[1];
    std::string channel_name = args[2];

    Client *theClient = get_client_by_nickname(user_name);
    Channel *theChannel = get_channel_by_name(channel_name);

    if (!theChannel) {
        client->send_msg("Le canal" + channel_name + "n'existe pas.");
        return;
    }

    if (!theClient) {
        client->send_msg("\033[1;31mLe client " + user_name + " n'a pas été trouvé.\033[0m");
        return;
    }

    if (theChannel->is_client(theClient)) {
        client->send_msg(user_name + "est déjà dans le canal " + channel_name);
        return;
    }

    theChannel->add_client(theClient);
    client->send_msg("vous avez invité " + user_name + "à rejoindre le canal" + channel_name);
    theClient->send_msg("vous avez été invité à rejoindre le canal" + channel_name);
}
