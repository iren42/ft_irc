#include "Server.hpp"

void Server::do_action_nick(Client *client, std::vector<std::string> args)
{
	std::cout << "action nick" << std::endl;

	if (args.size() != 2)
	{
		client->send_msg("Bad argument number. Format : NICK new_nickname");
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "NICK"));
		return;
	}
	std::string nickname = args[1];

	if (nickname.length() > 9) nickname = nickname.substr(0, 9);

	if (nickname == "")
	{
		client->send_msg("ERREUR : Le nickname vide est interdit.");
		client->reply(ERR_ERRONEUSNICKNAME(nickname));
		return;
	}

	if (get_client_by_nickname(nickname) && client->getNickname() != nickname)
	{
		client->send_msg(
				"ERREUR : Le nickname " + nickname + " est déjà utilisé");
		client->reply(ERR_NICKNAMEINUSE(nickname));
		return;
	}

	if (nickname[0] == '#' || nickname[0] == ':')
	{
		client->send_msg("ERREUR : Le nickname ne peut commencer par # ou :");
		client->reply(ERR_ERRONEUSNICKNAME(nickname));
		return;
	}

	if (client->getNickname() == "")
		client->reply(RPL_WELCOME(nickname));
	std::string old_prefix = client->getPrefix();
	client->setNickname(nickname);

	client->getServer()->send_all(old_prefix + " " + RPL_NICK(nickname) + "\r\n");

	std::string msg = "Nickname changé en ";
	msg.append(args[1]);
	client->send_msg(msg);

}
