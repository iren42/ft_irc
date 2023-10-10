#include "Server.hpp"

void Server::do_action_part(Client *client, std::vector<std::string> args) {

    if (args.size() < 2) {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickname(), "PART"));
        client->send_msg(
                "ERREUR : La commande PART nécessite un argument (nom du canal).");
        return;
    }

    std::string channelName = args[1];

    Channel *channel = client->getServer()->getChannels()[channelName];

    if (channel) {
        channel->replyAll(client->getPrefix() + " " + RPL_PART(channel->getName(), ""));
        channel->remove_client(client);
        client->send_msg("Vous avez quitté le canal " + channelName);

        if (channel->isEmpty()) {
            delete channel;
            _map_channel.erase(_map_channel.find(channelName));
        }
    } else {
        client->reply(ERR_NOTONCHANNEL(client->getNickname(), channelName));
        client->send_msg(
                "ERREUR : Vous n'êtes pas dans le canal " + channelName);

    }
}
