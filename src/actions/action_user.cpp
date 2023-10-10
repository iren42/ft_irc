#include "Server.hpp"

void Server::do_action_user(Client *client, std::vector<std::string> args) {
    if (args.size() < 5) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "USER"));
        client->send_msg("ERREUR : La commande USER nécessite au moins quates arguments.");
        return;
    }

    std::string nickname = args[1];
    std::string username = args[2];
    std::string hostname = args[3];

    if (nickname == "") {
		client->reply(ERR_ERRONEUSNICKNAME(nickname));
        client->send_msg("ERREUR : Le nickname vide est interdit.");
        return;
    }

    if (get_client_by_nickname(nickname) && client->getNickname() != nickname) {
		client->reply(ERR_NICKNAMEINUSE(nickname));
        client->send_msg("ERREUR : Le nickname " + nickname + " est déjà utilisé");
        return;
    }

    if (nickname[0] == '#' || nickname[0] == ':') {
		client->reply(ERR_ERRONEUSNICKNAME(nickname));
        client->send_msg("ERREUR : Le nickname ne peut commencer par # ou :");
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
