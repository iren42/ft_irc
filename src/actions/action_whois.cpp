#include "Server.hpp"

void Server::do_action_whois(Client *client, std::vector<std::string> args) {
    if (args.size() < 2) {
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "WHOIS"));
        client->send_msg(
                "Erreur : la syntaxe devrait etre /WHOIS <nick>\nExemple : 'WHOIS john'");
    }
        /*
         * Write this message on the client side:
         * <nick> is <username>
         * <nick> on <channels>
         */
    else {
        std::string nick = args.back();
        std::string buf;
        CLIENTS::iterator it = _map_client.begin();
        while (it != _map_client.end()) {
            if (((*it).second)->getNickname() == nick) {
                buf.append(nick + " est " + (*it).second->getRealname() + "\n");
                buf.append(nick + " sur");
                CHANNELS::iterator ita = _map_channel.begin();
                while (ita != _map_channel.end()) {
                    if (((*ita).second)->is_client((*it).second)) {
                        buf.append(" " + (*ita).first);
                    }
                    ita++;
                }
                client->send_msg(buf);
                return;
            }
            it++;
        }
		client->reply(ERR_NOSUCHNICK(client->getNickname(), nick));
        client->send_msg("ERR_NOSUCHNICK");
    }
}
