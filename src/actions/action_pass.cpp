#include "Server.hpp"

void Server::do_action_pass(Client *client, std::vector<std::string> args) {
	if (args.size() < 2) {
	client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PASS"));	
		client->send_msg("Erreur : la syntaxe devrait etre /PASS <mot de passe>");
	}
	else if (client->isVerified())
	{
	client->reply(ERR_ALREADYREGISTERED(client->getNickname()));	
		client->send_msg("Vous etes deja connecte");
	}
	else if (getPass() == args.back()) {
		client->setVerified(true);
		client->send_msg("\033[1;32mMot de passe correct.\n\033[0m"
				"Choisissez votre surnom avec /NICK <surnom>");
	} else {
	client->reply(ERR_PASSWDMISMATCH(client->getNickname()));	
		client->send_msg("\033[1;31mMot de passe incorrect. Veuillez recommencer.\033[0m");
	}
}
