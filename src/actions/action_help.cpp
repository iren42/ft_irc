#include "Server.hpp"

void Server::do_action_help(Client *client, std::vector<std::string> args) {
  if (args.size() == 1) {
    client->send_msg(
        "*** List of all IRC commands:\n*** NICK, USER, JOIN, PART, MSG, QUIT, "
        "LIST, WHOIS,\n*** ME, PASS, KICK, INVITE, TOPIC, MODE, NAMES, INTRO\n"
        "Are you a new user? Try '/HELP intro'");
  } else if (args.size() > 2) {
    client->send_msg("Syntax: /HELP [command name]");
    client->send_msg("For example, try '/HELP NICK'");
  } else {
    std::string cmd = args.back();
    // TODO ASK USER to enter the server password upon connection
    if (cmd == "intro") {
      client->send_msg(
          "Welcome to our IRC server\nIRC (Internet Relay Chat) is a "
          "multi-user, multi-channel chatting system. It's totally free!\nTo "
          "start chatting, you must register your connection with either /USER "
          "or /NICK, then you can join a channel with /JOIN <channel> "
          "[<key>].\nOur list of channels is available with the command /LIST");
      client->send_msg("Try '/HELP user' or '/HELP nick'");
    } else if (cmd == "nick") {
      client->send_msg("Change the nickname by which you are known.\nNicknames "
          "are limited to 9 characters.");
      client->send_msg("Syntax: /NICK <YourNickname>");
    } else if (cmd == "user") {
      client->send_msg(
          "This command is used at the beginning of a connection to specify "
          "the username, hostname, real name of the connecting client");
      client->send_msg("Syntax: /USER <username> <hostname> <realname>");
    } else if (cmd == "join") {
      client->send_msg(
          "Causes a user to join the channel specified.\nIf the channel does "
          "not exist already, it will be created and you will be in charge of "
          "the new channel and be a channel operator");
      client->send_msg("Syntax: /JOIN <channel> [<key>]");
    }

    else if (cmd == "part") {
      client->send_msg("Causes a user to leave a channel");
      client->send_msg("Syntax: /PART <channel> [<message>]");
    } else if (cmd == "msg") {
      client->send_msg(
          "Send to <nickname> a message that only that person can read.");
      client->send_msg(
          "Syntax: /MSG <nick | channel> [message]\nFor example, '/MSG John "
          "Salut toi !'\n'/MSG #thisChannel Salut tout le monde !'");
    } else if (cmd == "quit") {
      client->send_msg("Exits IRC (also leaves any channels you may be on).");
      client->send_msg("Syntax: /QUIT [optional farewell message]");
    } else if (cmd == "list") {
      client->send_msg(
          "Lists IRC channels, number of users, and topic for each.");
      client->send_msg("Syntax: /LIST");
    }

    else if (cmd == "whois") {
      client->send_msg("Shows information about the nick specified.");
      client->send_msg("Syntax: /WHOIS <nickname>");
    } else if (cmd == "me") {
      client->send_msg("Display a pink message on a channel.");
      client->send_msg("Syntax: /ME <message>\nFor example, '/ME sing Here "
          "Comes The Sun - The Beatles'");
    } else if (cmd == "kick") {
      client->send_msg("Forcibly remove a user from a channel. This command "
          "can only be used by a channel operator");
      client->send_msg("Syntax: /KICK <channel> <user> [<comment>]");
    } else if (cmd == "invite") {
      client->send_msg("Invites <nickname> to the channel <channel>. <channel> "
          "does not have to exist, but if it does, only members "
          "of the channel are allowed to invite other clients.");
      client->send_msg("Syntax: /INVITE <nickname> <channel>");
    } else if (cmd == "topic") {
      client->send_msg(
          "The TOPIC command is used to change or view the topic of a channel. "
          "The topic for channel <channel> is returned if there is no <topic> "
          "given. If the <topic> parameter is present, the topic for that "
          "channel will be changed, if the channel modes permit this action.");
      client->send_msg("Syntax: /TOPIC <channel> [<topic>]");
    } else if (cmd == "mode") {
      client->send_msg("The MODE command is dual-purpose. It can be used to "
          "set both user and channel modes.");
      client->send_msg("Syntax: /MODE <channel> <flags> [<args>]\n/MODE "
          "<nickname> <flags> (user)");
    } else if (cmd == "help") {
      client->send_msg(
          "The HELP command. Display to a user a command description.");
      client->send_msg("Syntax: /HELP [optional command name]");
    } else if (cmd == "pass") {
      client->send_msg("The PASS command is used to set a 'connection "
          "password'. The password can and must be set before any "
          "attempt to register the connection is made.");
      client->send_msg("Syntax: /PASS <password>");
    } else
      client->send_msg("Sorry. We could not find your command.");
  }
}
