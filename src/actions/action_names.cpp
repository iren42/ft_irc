#include "Server.hpp"

void Server::do_action_names(Client *client, std::vector<std::string> args) {

    if (args.size() < 2) {
        client->send_msg("Utilisation : /NAMES <canal>");
        return;
    }

    std::string nomCanal = args[1];
    std::map<std::string, Channel *>::iterator it = _map_channel.find(nomCanal);


    if (it == _map_channel.end()) {
        client->send_msg("Le canal " + nomCanal + " n'a pas été trouvé.");
        return;
    }
    Channel *canal = it->second;

    std::string listeUtilisateurs;
    for (std::vector<Client *>::const_iterator it2 = canal->getClients().begin();
         it2 != canal->getClients().end(); ++it2) {
        listeUtilisateurs += (*it2)->getNickname() + "\n";
    }

    std::string message = "Utilisateurs dans le canal " + canal->getName() + " :\n";
    message += "----------------------------------------\n";
    message += listeUtilisateurs + "\n";
    message += "----------------------------------------";
    client->send_msg(message);
}