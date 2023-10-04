#include "Server.hpp"

void Server::do_action_pass(Client *client, std::vector<std::string> args)
{
	if (args.size() != 2)
	{
		client->send_msg(
				"Erreur : la syntaxe devrait etre '/PASS <mot de passe>'");
	} else
	{
		if (getPass() == args.back())
		{
			client->setVerified(true);
			client->send_msg(BOLDGREEN + "Mot de passe correct.\n" + RESET +
							 "Choisissez votre nickname avec '/NICK <surnom>'");
		} else
		{
			client->send_msg(
					BOLDRED + "Mot de passe incorrect. Veuillez recommencer." +
					RESET);
		}
	}
}
