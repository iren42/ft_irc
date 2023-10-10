#include "Server.hpp"


void Server::do_action_names(Client *client, std::vector<std::string> args)
{

    if (args.size() < 2)
    {
        std::stringstream ss;
        ss << "Liste des utilisateurs" << std::endl;;
        ss << "--------------------------------" << std::endl;;

        CHANNELS::iterator it;
        for (it = _map_channel.begin(); it != _map_channel.end(); ++it)
        {
            const std::string &canalName = it->first;
            Channel *canal = it->second;

            ss << canalName << " : ";

            bool started = false;
            for (std::vector<Client *>::const_iterator it = canal->getClients().begin();
                 it != canal->getClients().end(); ++it)
            {
                if (started)
                    ss << ", ";
                started = true;
				if(canal->is_op(*it))
					ss<<"@";
                ss << (*it)->getNickname();
            }
            ss << "\n";
        }
        std::vector<Client *> no_channel;

        CLIENTS::iterator it2 = _map_client.begin();
        while (it2 != _map_client.end())
        {
            Client *client2 = it2->second;
            CHANNELS::iterator it3;
            bool find = false;

            for (it3 = _map_channel.begin();
                 it3 != _map_channel.end() && !find; ++it3)
                find = it3->second->is_client(client2);
            if (!find && client2->getNickname()!= "")
                no_channel.push_back(client2);

            it2++;
        }

        if (!no_channel.empty())
        {
            ss << "Sans canal : ";
            std::vector<Client *>::iterator it3;
            bool started = false;
            for (it3 = no_channel.begin(); it3 != no_channel.end(); ++it3)
            {
                if (started)
                    ss << ", ";
                started = true;
                ss << (*it3)->getNickname();
            }
        }

        client->send_msg(ss.str());
        return;
    }

    std::string nomCanal = args[1];
    CHANNELS::iterator it = _map_channel.find(nomCanal);


    if (it == _map_channel.end())
    {
        client->send_msg("Le canal " + nomCanal + " n'a pas été trouvé.");
        return;
    }
    Channel *canal = it->second;

    std::string listeUtilisateurs;
    for (std::vector<Client *>::const_iterator it2 = canal->getClients().begin();
         it2 != canal->getClients().end(); ++it2)
    {
        listeUtilisateurs += (*it2)->getNickname() + "\n";
    }

    std::stringstream ss;

    std::string message =
            "Utilisateurs dans le canal " + canal->getName() + " :";

    if (canal->getLimit() > 0)
        ss << "[" << canal->get_nb_clients() << "/" << canal->getLimit()
           << "]\n";
    else
        ss << "[" << canal->get_nb_clients() << "]\n";

    message += ss.str();
    message += "----------------------------------------\n";
    message += listeUtilisateurs;
    message += "----------------------------------------";
    client->send_msg(message);
}