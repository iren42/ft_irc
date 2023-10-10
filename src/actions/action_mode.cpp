#include "Server.hpp"

void Server::do_action_mode(Client *client, std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		client->send_msg(
				"ERREUR : Utilisation : /MODE <nom canal> <mode_param> [args].");
		client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
		return;
	}

	if (args[1][0] == '#')
		return do_action_mode_channel(client, args);
}

void
Server::do_action_mode_channel_limit(Client *client, Channel *channel,
									 std::string cmd,
									 std::vector<std::string> args)
{
	if (cmd == "-l")
	{
		channel->setLimit(-1);
		client->send_msg(
				BOLDGREEN + "La limite du channel " + channel->getName() +
				" a été retiré." + RESET);
		return;
	} else if (cmd == "+l")
	{
		if (args.size() < 4)
		{
			client->send_msg(
					"ERREUR : Utilisation : /MODE <nom canal> +l <limite>.");
			client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
			return;
		}
		int limit = atoi(args[3].c_str());
		channel->setLimit(limit);

		std::string myString;
		std::stringstream ss;
		ss << limit;

		client->send_msg(
				BOLDGREEN + "La limite du channel " + channel->getName() +
				" a été fixé à " + ss.str() + "." + RESET);
		return;
	}
}

void
Server::do_action_mode_channel_key(Client *client, Channel *channel,
								   std::string cmd,
								   std::vector<std::string> args)
{
	if (cmd == "-k")
	{
		channel->setLockPass("");
		client->send_msg(
				BOLDGREEN + "Le mot de passe du channel " + channel->getName() +
				" a été retiré." + RESET);
		return;
	} else if (cmd == "+k")
	{
		if (args.size() < 4)
		{
			client->send_msg(
					"ERREUR : Utilisation : /MODE <nom canal> +k <mdp>.");
			client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
			return;
		}
		std::string pass = args[3].c_str();
		channel->setLockPass(pass);

		client->send_msg(
				BOLDGREEN + "Le channel " + channel->getName() +
				" a un nouveau mot de passe." + RESET);
		return;
	}
}

void
Server::do_action_mode_channel(Client *client, std::vector<std::string> args)
{
	std::string channelName = args[1];

	Channel *channel = get_channel_by_name(channelName);

	if (!channel)
	{
		client->reply(ERR_NOSUCHCHANNEL(client->getNickname(), channelName));
		client->send_msg(
				BOLDRED + "Le canal " + channelName + " n'a pas été trouvé." +
				RESET);
		return;
	}
	if (args.size() == 2)
	{
		std::string modes = "";
		if (channel->isModeInvite())
			modes += "i";
		if (channel->getLockPass() != "")
			modes += "k";
		if (channel->getLimit() > 0)
			modes += "l";
		if (channel->isModeTopicOp())
			modes += "t";
		client->reply(
				RPL_CHANNELMODEIS(client->getNickname(), channelName, modes,
								  ""));
		return;
	}

	std::string &cmd = args[2];
	if (cmd == "+b" || cmd == "-b")
		return;

	if (!channel->is_op(client))
	{
		channel->setLimit(-1);
		client->reply(ERR_CHANOPRIVSNEEDED(client->getNickname(), channelName));
		client->send_msg(
				BOLDRED + "Vous n'êtes pas opérateurs sur le channel " +
				channelName + "." + RESET);
		return;
	}


	if (cmd == "+l" || cmd == "-l")
		do_action_mode_channel_limit(client, channel, cmd, args);

	if (cmd == "+k" || cmd == "-k")
		do_action_mode_channel_key(client, channel, cmd, args);


	if (cmd == "+i")
	{
		channel->setModeInvite(true);
		client->send_msg(BOLDGREEN + "Le canal " + channel->getName() +
						 " est passé en mode invité " + RESET);
	}
	if (cmd == "-i")
	{
		channel->setModeInvite(false);
		client->send_msg(BOLDGREEN + "Le canal " + channel->getName() +
						 " est passé en mode non invité " + RESET);
	}

	if (cmd == "+t")
	{
		channel->setModeTopicOp(true);
		client->send_msg(
				BOLDGREEN + "Les topics du canal " + channel->getName() +
				" ne peuvent plus être modifié que par les ops " + RESET);
	}
	if (cmd == "-t")
	{
		channel->setModeTopicOp(false);
		client->send_msg(
				BOLDGREEN + "Les topics du canal " + channel->getName() +
				" peuvent être modifié par tous " + RESET);
	}

	if (cmd == "-o" || cmd == "+o")
	{
		if (args.size() < 4)
		{
			client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
			client->send_msg("ERREUR : Utilisation : /MODE <nom canal> " + cmd +
							 " <nickname>.");
			return;
		}
		Client *opc = get_client_by_nickname(args[3]);

		if (!opc || !channel->is_client(opc))
		{
			client->reply(ERR_USERNOTINCHANNEL(client->getNickname(),
											   args[3],
											   channelName));
			return;
		}

		if (cmd[0] == '+')
		{
			if (channel->is_op(opc))
			{
				client->send_msg(
						BOLDRED + "Le client " + opc->getNickname() +
						" est déjà op sur le canal" + channel->getName() +
						RESET);
				return;
			}
			client->send_msg(
					BOLDGREEN + "Le client " + opc->getNickname() +
					" est maintenant op sur le canal" +
					channel->getName() +
					RESET);
			client->getServer()->send_all(
					client->getPrefix() + " MODE " + channelName + " +o " +
					opc->getNickname() + "\r\n");
			channel->add_op(opc);
		}
		if (cmd[0] == '-')
		{
			if (!channel->is_op(opc))
			{
				client->send_msg(
						BOLDRED + "Le client " + opc->getNickname() +
						" n'est pas op sur le canal" + channel->getName() +
						RESET);
				client->reply(
						ERR_NEEDMOREPARAMS(client->getNickname(), "MODE"));
				return;
			}
			client->send_msg(
					BOLDGREEN + "Le client " + opc->getNickname() +
					" n'est plus op sur le canal" + channel->getName() +
					RESET);
			client->getServer()->send_all(
					client->getPrefix() + " MODE " + channelName + " -o " +
					opc->getNickname() + "\r\n");
			channel->remove_op(opc);
		}
	}

}

