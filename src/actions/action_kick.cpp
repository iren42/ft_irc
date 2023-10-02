#include "Server.hpp"

void Server::do_action_kick(Client *client, std::vector<std::string> args) {

    if (args.size() < 3) {
        client->send_msg("Utilisation : /KICK <canal> <utilisateur> [raison]");
        return;
    }

    std::string channelName = args[1];
    std::string userName = args[2];

    std::map<std::string, Channel *>::iterator it = _map_channel.find(channelName);

    if (it == _map_channel.end()) {
        client->send_msg("\033[1;31mLe canal " + channelName + " n'a pas été trouvé.\033[0m");
        return;
    }

    Channel *canal = it->second;

    if (!canal->is_op(client)) {
        client->send_msg("Vous n'avez pas les droits d'opérateur pour exécuter cette commande.");
        return;
    }

    Client *badClient = get_client_by_nickname(userName);

    if (!badClient) {
        client->send_msg("\033[1;31mLe client " + userName + " n'a pas été trouvé.\033[0m");
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
    canal->remove_client(badClient);
    badClient->send_msg(message);

}