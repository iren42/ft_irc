#include "Server.hpp"

void Server::do_action_kick(Client *client, std::vector<std::string> args) {

    if (args.size() < 3) {
        client->send_msg("Utilisation : /KICK <canal> <utilisateur> [raison]");
        return;
    }

    std::string channelName = args[1];
    std::string userName = args[2];

    Channel *theChannel = get_channel_by_name(channelName);


    if (!theChannel) {
        client->send_msg("Le canal" + channelName + "n'existe pas.");
        return;
    }

    if (!theChannel->is_op(client)) {
        client->send_msg("Vous n'avez pas les droits d'opérateur pour exécuter cette commande.");
        return;
    }

    Client *badClient = get_client_by_nickname(userName);

    if (!badClient) {
        client->send_msg(BOLDRED + "Le client " + userName + " n'a pas été trouvé."+RESET);
        return;
    }


    std::string message = "Vous avez été renvoyé de " + channelName + " par " + client->getNickname();

    if (args.size() > 3) {
        message += "\nRaison : ";

        for (size_t i = 3; i < args.size(); i++) {
            message += args[i];
            if (i < args.size() - 1) {
                message += " ";
            }
        }
    }
    theChannel->remove_client(badClient);
    badClient->send_msg(message);
    client->send_msg("Client " + userName + " a bien été renvoyé");

}