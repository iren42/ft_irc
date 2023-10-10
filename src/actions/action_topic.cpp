#include "Server.hpp"

void Server::do_action_topic(Client *client, std::vector<std::string> args)
{

    if (args.size() < 2)
    {
        client->send_msg("Utilisation : /TOPIC <nom-du-canal> [nouveau-sujet]");
        return;
    }

    std::string channelName = args[1];

    Channel *channel = get_channel_by_name(channelName);

    if (!channel)
    {
        client->send_msg("Le canal " + channelName + " n'existe pas.");
        return;
    }


    std::string currentTopic = channel->getTopic();

    if (args.size() > 2)
    {
        if (channel->isModeTopicOp() && !channel->is_op(client))
        {
            client->send_msg(BOLDRED + "Vous n'êtes pas opérateurs sur le channel " + channelName + "." + RESET);
            return;
        }

        std::string newTopic = ""; // Supprime le deux-points

        for (size_t i = 2; i < args.size(); i++)
        {
            newTopic += args[i];
            if (i < args.size() - 1)newTopic += " ";
        }

        channel->setTopic(newTopic);

        std::string topicMessage = "Le sujet du canal a été changé par " + client->getNickname() + " : " + newTopic;

        for (std::vector<Client *>::const_iterator it2 = channel->getClients().begin();
             it2 != channel->getClients().end(); ++it2)
        {
            (*it2)->send_msg(topicMessage);
        }


        client->send_msg("Sujet du canal " + channelName + " mis à jour : " + newTopic);
    } else
        client->send_msg("Sujet actuel du canal " + channelName + " : " + currentTopic);

    if (channel->getTopic() == "")
        client->reply(RPL_NOTOPIC(client->getNickname(), channel->getName()));
    else
        client->reply(RPL_TOPIC(client->getPrefix(), channel->getName(), channel->getTopic()));

}