#include "Server.hpp"

void Server::do_action_nick(Client *client, std::vector<std::string> args) {
    std::cout << "action nick" << std::endl;

    if (args.size() != 2) {
        client->send_msg("Bad argument number. Format : NICK new_nickname");
        return;
    }
    std::string nickname = args[1];

	if (nickname.length() > 9) nickname = nickname.substr(0, 9);

    if (nickname == "undefined") {
        client->send_msg("ERREUR : Le nickname undefined est interdit.");
        return;
    }

    if (get_client_by_nickname(nickname)) {
        client->send_msg("ERREUR : Le nickname " + nickname + " est déjà utilisé");
        return;
    }

    if (nickname[0] == '#'){
        client->send_msg("ERREUR : Le nickname ne peut commencer par #");
        return;
    }

    client->setNickname(nickname);
    std::string msg = "Nickname changé en ";
    msg.append(args[1]);
    client->send_msg(msg);

}