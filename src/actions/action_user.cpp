#include "Server.hpp"

void Server::do_action_user(Client *client, std::vector<std::string> args) {
    if (args.size() < 5) {
        client->send_msg("ERREUR : La commande USER nécessite au moins quates arguments.");
        return;
    }

    std::string nickname = args[1];
    std::string username = args[2];
    std::string hostname = args[3];

    if (nickname == "") {
        client->send_msg("ERREUR : Le nickname vide est interdit.");
        return;
    }

    if (get_client_by_nickname(nickname) && client->getNickname() != nickname) {
        client->send_msg("ERREUR : Le nickname " + nickname + " est déjà utilisé");
        return;
    }

    if (nickname[0] == '#'){
        client->send_msg("ERREUR : Le nickname ne peut commencer par #");
        return;
    }

    std::string realname;
    for (size_t i = 4; i < args.size(); i++) {
        realname += args[i];
        if (i < args.size() - 1) {
            realname += " ";
        }
    }

    client->setNickname(nickname);
    client->setUsername(username);
    if (hostname != "*")
        client->setHostname(hostname);
    client->setRealname(realname);

    client->send_msg("Votre profil a été mis à jour avec succès.");
}