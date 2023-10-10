#include "Server.hpp"

void Server::do_action_part(Client *client, std::vector<std::string> args)
{

	if (args.size() < 2)
	{
		client->send_msg(
				"ERREUR : La commande PART nécessite un argument (nom du canal).");
		return;
	}

	std::string channelName = args[1];

	Channel *channel = client->getServer()->getChannels()[channelName];

	if (channel)
	{
		channel->remove_client(client);
        channel->replyAll(RPL_PART(channel->getName(), ""));
        client->send_msg("Vous avez quitté le canal " + channelName);

		if (channel->isEmpty())
		{
			delete channel;
			_map_channel.erase(_map_channel.find(channelName));
		}
	} else
		client->send_msg(
				"ERREUR : Vous n'êtes pas dans le canal " + channelName);


}