#include "Server.hpp"

void Server::do_action_pass(Client *client, std::vector<std::string> args) {
    if (args.size() != 2) {
        client->send_msg("Erreur : la syntaxe devrait etre '/PASS <mot de passe>'");
    } else {
        if (getPass() == args.back()) {
            client->setVerified(true);
            client->send_msg("Mot de passe correct.\n"
                             "Choisissez votre surnom avec '/NICK <surnom>'");
        } else {
            client->send_msg("Mot de passe incorrect. Veuillez recommencer.");
        }
    }
}
