#include "Server.hpp"

void Server::init_map_action() {
    _map_cmd["ping"] = &Server::do_action_ping;
    _map_cmd["cap"] = &Server::do_action_cap;
    _map_cmd["who"] = &Server::do_action_who;
    _map_cmd["pass"] = &Server::do_action_pass;
    _map_cmd["nick"] = &Server::do_action_nick;
    _map_cmd["user"] = &Server::do_action_user;
    _map_cmd["join"] = &Server::do_action_join;
    _map_cmd["part"] = &Server::do_action_part;
    _map_cmd["privmsg"] = &Server::do_action_privmsg;
    _map_cmd["notice"] = &Server::do_action_notice;
    _map_cmd["help"] = &Server::do_action_help;
    _map_cmd["quit"] = &Server::do_action_quit;
    _map_cmd["list"] = &Server::do_action_list;
    _map_cmd["whois"] = &Server::do_action_whois;
    _map_cmd["names"] = &Server::do_action_names;
    _map_cmd["kick"] = &Server::do_action_kick;
    _map_cmd["invite"] = &Server::do_action_invite;
    _map_cmd["topic"] = &Server::do_action_topic;
    _map_cmd["mode"] = &Server::do_action_mode;
}

void Server::client_disconnect(Client *client) {
    int fd = client->getFd();
    CHANNELS::iterator it;
    std::vector<std::string>::iterator it_to_remove;
    std::vector<std::string> chan_to_remove;

    for (it = _map_channel.begin(); it != _map_channel.end(); it++) {
        it->second->remove_client(_map_client[fd]);
        if (it->second->get_nb_clients() == 0)
            chan_to_remove.push_back(it->second->getName());
    }

    for (it_to_remove = chan_to_remove.begin();
         it_to_remove != chan_to_remove.end(); ++it_to_remove) {
        delete (_map_channel[*it_to_remove]);
        _map_channel.erase(*it_to_remove);
    }

    epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd,
              0); //retrait du client de l'evenement epoll_ctl
    delete client;
    _map_client.erase(fd);
    close(fd);
    std::cout << "Client [" << fd << "] disconnected." << std::endl;
    return;
}

std::string Server::handle_client(int client_fd, Client *client) {
    if (client->get_swtch() == 0) {
        std::cout << "************** clear [" << client->get_msg() << "]"
                  << std::endl;
        client->get_msg().clear();
    }
    char tmp[16384] = {0};
    int r = recv(client_fd, tmp, 16384,
                 0); // recevoir jusque 16384octet de donnée de ckient_fd
    std::cout << "recv = '" << tmp << "'" << std::endl;
    if (r == -1) {
        perror("Error while receiving data.");
        return std::string();
    } else if (r == 0) {
        std::cout << "client disconnection"
                  << std::endl; // GERER LA DISCONNEXION Client
        client_disconnect(client);
        return std::string();
    }
    client->swtch_on();
    client->get_msg().append(tmp, r);

    // recherche de la premiere occurence de "\r\n" ou "\n"
    size_t newline = client->get_msg().find("\r\n");
    if (newline == std::string::npos) { // npos = find n'a pas trouvé ce qu'il cherchait
        newline = client->get_msg().find("\n");
    }
    // si une newline est trouvée dans le tampon de msg = msg valide
    if (newline != std::string::npos) {
        client->swtch_off();
//        client->get_msg().erase(newline);

        return (client->get_msg());
    }
    return std::string("");
}

void Server::parse_action(std::string message, Client *client) {
    std::string firstWord;

    size_t spacePosition = message.find(' ');
    if (spacePosition != std::string::npos)
        firstWord = message.substr(0, spacePosition);
    else
        firstWord = message;

    for (unsigned int i = 0; i < firstWord.length(); i++)
        firstWord.at(i) = (char) std::tolower(firstWord.at(i));

    std::vector<std::string> arguments;
    std::string motActuel;

    // TODO a ameliorer avec les fonctions cpp
    for (unsigned int i = 0; i < message.length(); i++)
        if (message.at(i) != ' ')
            motActuel += message.at(i);
        else if (!motActuel.empty()) {
            arguments.push_back(motActuel);
            motActuel.clear();
        }

    if (!motActuel.empty())
        arguments.push_back(motActuel);


    if (_map_cmd.find(firstWord) != _map_cmd.end()) {
        if ((!client->isVerified()
             || !client->isNickSet())
            && firstWord != "pass"
            && firstWord != "cap"
            && firstWord != "quit"
            && firstWord != "nick"
            && firstWord != "user"
            && firstWord != "help") {
            if (!client->isVerified()) {
                client->reply(ERR_NOTREGISTERED(client->getNickname()));
                client->send_msg(
                        BOLDRED + "Vous n'êtes pas identifié, utilisez la "
                                  "commande /PASS <mdp>." + RESET);
            } else if (client->getNickname() == "")
                client->send_msg(
                        BOLDRED + "Vous ne vous êtes pas renommé, utilisez la"
                                  "commande /NICK nickname." + RESET);

            return;
        }
        ((this->*_map_cmd[firstWord]))(client, arguments);
    } else {
        client->send_msg(firstWord +
                         " n'est pas une commande. Vous pouvez utiliser la commande /HELP");

    }
}
