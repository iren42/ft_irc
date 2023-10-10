#include "Server.hpp"

// send a message to every client on channel <target> only when sender joined
// that channel beforehand
void Server::noticeChannel(Client *sender, std::string target,
                           std::vector<std::string> args) {
    CHANNELS::iterator it = _map_channel.find(target);
    if (it != _map_channel.end()) {
        if ((((*it).second)->is_client(sender)) == true) {
            std::vector<Client *> vec = (((*it).second)->getClients());
            std::vector<Client *>::iterator ita = vec.begin();

            (*it).second->replyAll(sender->getPrefix() + " "+RPL_NOTICE(target, createMsg(args)));

            while (ita != vec.end()) {
                (*ita)->send_msg("[" + target + "] " + ": " + createMsg(args),
                                 sender->getNickname());
                ita++;
            }
        }
    }
}

// send a message to a Client
void Server::noticeClient(Client *sender, std::string target,
                          std::vector<std::string> args) {
    CLIENTS::iterator receiver = findClient(target);
    if (receiver != _map_client.end()) {
        ((*receiver).second)->send_msg(createMsg(args), sender->getNickname());
        ((*receiver).second)->reply(RPL_NOTICE(target, createMsg(args)));

    }
}

void Server::do_action_notice(Client *sender, std::vector<std::string> args) {
    if (!sender->isVerified() || args.size() <= 2)
        return;
    else {
        // case 1: target has '#' as the 1st char, it may be an existing channel
        if (args.at(1).at(0) == '#') {
            if (isInMapChannel(args.at(1)))
                noticeChannel(sender, args.at(1), args);
        }
            // case 2: target is a client
        else
            noticeClient(sender, args.at(1), args);
    }
}
