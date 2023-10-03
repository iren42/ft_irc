#include "Server.hpp"

void Server::do_action_mode(Client *client, std::vector<std::string> args) {
    if (args.size() < 3) {
        client->send_msg("ERREUR : Utilisation : /MODE <nom canal> <mode_param> [args].");
        return;
    }

    return do_action_mode_channel(client, args);
}

void
Server::do_action_mode_channel_limit(Client *client, Channel *channel, std::string cmd, std::vector<std::string> args) {
    if (cmd == "-l") {
        channel->setLimit(-1);
        client->send_msg("\033[1;32mLa limite du channel " + channel->getName() + " a été retiré.\033[0m");
        return;
    } else if (cmd == "+l") {
        if (args.size() < 4) {
            client->send_msg("ERREUR : Utilisation : /MODE <nom canal> +l <limite>.");
            return;
        }
        int limit = atoi(args[3].c_str());
        channel->setLimit(limit);

        std::string myString;
        std::stringstream ss;
        ss << limit;

        client->send_msg(
                "\033[1;32mLa limite du channel " + channel->getName() + " a été fixé à " + ss.str() + ".\033[0m");
        return;
    }
}

void
Server::do_action_mode_channel_key(Client *client, Channel *channel, std::string cmd, std::vector<std::string> args) {
    if (cmd == "-k") {
        channel->setLockPass("");
        client->send_msg("\033[1;32mLe mot de passe du channel " + channel->getName() + " a été retiré.\033[0m");
        return;
    } else if (cmd == "+k") {
        if (args.size() < 4) {
            client->send_msg("ERREUR : Utilisation : /MODE <nom canal> +k <mdp>.");
            return;
        }
        std::string pass = args[3].c_str();
        channel->setLockPass(pass);

        client->send_msg(
                "\033[1;32mLe channel " + channel->getName() + " a un nouveau mot de passe.\033[0m");
        return;
    }
}

void Server::do_action_mode_channel(Client *client, std::vector<std::string> args) {
    std::string channelName = args[1];

    Channel *channel = get_channel_by_name(channelName);

    if (!channel) {
        client->send_msg("\033[1;31mLe canal " + channelName + " n'a pas été trouvé.\033[0m");
        return;
    }

    if (!channel->is_op(client)) {
        channel->setLimit(-1);
        client->send_msg("\033[1;31mVous n'êtes pas opérateurs sur le channel " + channelName + ".\033[0m");
        return;
    }

    std::string &cmd = args[2];

    if (cmd == "+l" || cmd == "-l")
        do_action_mode_channel_limit(client, channel, cmd, args);

    if (cmd == "+k" || cmd == "-k")
        do_action_mode_channel_key(client, channel, cmd, args);


    if (cmd == "+i") {
        channel->setModeInvite(true);
        client->send_msg("\033[1;32mLe canal " + channel->getName() + " est passé en mode invité \033[0m");
    }
    if (cmd == "-i") {
        channel->setModeInvite(false);
        client->send_msg("\033[1;32mLe canal " + channel->getName() + " est passé en mode non invité \033[0m");
    }

    if (cmd == "+t") {
        channel->setModeTopicOp(true);
        client->send_msg("\033[1;32mLes topics du canal " + channel->getName() +
                         " ne peuvent plus être modifié que par les ops \033[0m");
    }
    if (cmd == "-t") {
        channel->setModeTopicOp(false);
        client->send_msg(
                "\033[1;32mLes topics du canal " + channel->getName() + " peuvent être modifié par tous \033[0m");
    }

    if (cmd == "-o" || cmd == "+o") {
        if (args.size() < 4) {
            client->send_msg("ERREUR : Utilisation : /MODE <nom canal> " + cmd + " <nickname>.");
            return;
        }
        Client *opc = get_client_by_nickname(args[4]);

        if (cmd[0] == '+') {
            if (channel->is_op(opc)) {
                client->send_msg(
                        "\033[1;31mLe client " + opc->getNickname() + " est déjà op sur le canal" + channel->getName() +
                        " \033[0m");
                return;
            }
            client->send_msg(
                    "\033[1;32mLe client " + opc->getNickname() + " est maintenant op sur le canal" +
                    channel->getName() +
                    " \033[0m");
            channel->add_op(opc);
        }
        if (cmd[0] == '-') {
            if (!channel->is_op(opc)) {
                client->send_msg(
                        "\033[1;31mLe client " + opc->getNickname() + " n'est pas op sur le canal" +
                        channel->getName() +
                        " \033[0m");
                return;
            }
            client->send_msg(
                    "\033[1;32mLe client " + opc->getNickname() + " n'est plus op sur le canal" + channel->getName() +
                    " \033[0m");
            channel->remove_op(opc);
        }
    }

}

