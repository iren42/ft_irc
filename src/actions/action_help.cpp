#include "Server.hpp"
/*
   void Server::do_action_help(Client *client, std::vector<std::string> args)
   {
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
} */
void Server::do_action_help(Client *client, std::vector<std::string> args)
{
  if (args.size() == 1)
  {
    client->send_msg(
        "*** Liste de toutes les commandes IRC :\n*** NICK, USER, JOIN, PART, MSG, QUIT, "
        "LIST, WHOIS,\n*** ME, PASS, KICK, INVITE, TOPIC, MODE, NAMES, INTRO\nEtes-vous "
        "un nouvel utilisateur ? Essayez '/HELP intro'");
  }
  else if (args.size() > 2)
  {
    client->send_msg("Syntaxe : /HELP [nom de la commande]");
    client->send_msg("Par exemple, '/HELP NICK'");
  }
  else 
  {
    std::string cmd = args.back();
    // TODO ajouter une condition au debut de chaque fonction do_action()
    if (cmd == "intro") 
    {
      client->send_msg(
          "Bienvenue sur notre serveur IRC\nIRC (Internet Relay Chat) est un "
          "systeme de discussion multi-utilisateurs et multi-canaux. C'est totalement gratuit !\nPour "
          "commencer a discuter, vous devez entrer le mot de passe du serveur. Voir '/HELP PASS'. "
          "Ensuite, vous devez enregistrer votre connexion avec /NICK (et /USER). Voir '/HELP NICK'. "
          "Enfin, vous pourrez rejoindre un canal de discussion avec /JOIN <canal> "
          "[<cle>].\nNotre liste de canaux est disponible avec la commande /LIST");
      client->send_msg("Vous ne savez plus par ou commencer ? Essayez '/HELP PASS'");
    }
    else if (cmd == "nick")
    {
      client->send_msg("Changez le surnom sous lequel vous etes connu.\nLes surnoms sont limites a 9 caracteres.");
      client->send_msg("Syntaxe : /NICK <VotreSurnom>");
    }
    else if (cmd == "user") 
    {
      client->send_msg(
          "Cette commande est utilisee au debut d'une connexion pour specifier "
          "le nom d'utilisateur, le nom d'hote et le nom reel du client connecte");
      client->send_msg("Syntaxe : /USER <nom d'utilisateur> <nom d'hote> <nom reel>");
    }
    else if (cmd == "join") 
    {
      client->send_msg(
          "Permet a un utilisateur de rejoindre le canal specifie.\n"
          "Si le canal n'existe pas encore, il sera cree et vous en serez l'operateur");
      client->send_msg("Syntaxe : /JOIN <canal> [<cle>]");
    }
    else if (cmd == "part") 
    {
      client->send_msg("Permet a un utilisateur de quitter un canal");
      client->send_msg("Syntaxe : /PART <canal> [<message>]");
    } 
    else if (cmd == "privmsg") 
    {
      client->send_msg(
          "Envoie un message privee a <nick>.");
      client->send_msg(
          "Syntaxe : /MSG <nick | canal> <message>\nPar exemple, '/PRIVMSG John Salut John'"
          "\n/PRIVMSG #unCanal Salut les membres de unCanal !");
    } 
    else if (cmd == "quit") 
    {
      client->send_msg("Quitte IRC (et quitte egalement tous les canaux auxquels vous pourriez etre connecte).");
      client->send_msg("Syntaxe : /QUIT [message d'adieu facultatif]");
    }
    else if (cmd == "list")
    {
      client->send_msg(
          "Affiche la liste des canaux IRC, le nombre d'utilisateurs et le sujet de chacun.");
      client->send_msg("Syntaxe : /LIST");
    }
    else if (cmd == "whois") 
    {
      client->send_msg("Affiche des informations sur le surnom specifie.");
      client->send_msg("Syntaxe : /WHOIS <surnom>");
    }
    else if (cmd == "me") 
    {
      client->send_msg("Affiche un message en rose dans un canal.");
      client->send_msg("Syntaxe : /ME <message>\nPar exemple, '/ME chante Here Comes The Sun - The Beatles'");
    }
    else if (cmd == "kick") 
    {
      client->send_msg("Retire de force un utilisateur d'un canal. "
          "Cette commande ne peut etre utilisee que par un operateur de canal.");
      client->send_msg("Syntaxe : /KICK <canal> <utilisateur> [<commentaire>]");
    }
    else if (cmd == "invite") 
    {
      client->send_msg("Invite <surnom> dans le canal <canal>. <canal> n'a pas besoin d'exister, "
          "mais si c'est le cas, seuls les membres du canal sont autorises a inviter de nouveaux membres.");
      client->send_msg("Syntaxe : /INVITE <surnom> <canal>");
    }
    else if (cmd == "topic") 
    {
      client->send_msg(
          "La commande TOPIC est utilisee pour changer ou afficher le sujet d'un canal. "
          "Le sujet du canal <canal> est renvoye s'il n'y a pas de <sujet> donne. "
          "Si le parametre <sujet> est present, le sujet du canal sera modifie, "
          "si les modes du canal le permettent.");
      client->send_msg("Syntaxe : /TOPIC <canal> [<sujet>]");
    }
    else if (cmd == "mode") 
    {
      client->send_msg("La commande MODE est polyvalente. Elle peut etre utilisee pour definir "
          "a la fois les modes utilisateur et les modes de canal.");
      client->send_msg("Syntaxe : /MODE <canal> <drapeaux> [<arguments>]\n"
          "/MODE <surnom> <drapeaux> (utilisateur)");
    }
    else if (cmd == "help") 
    {
      client->send_msg(
          "La commande HELP affiche a un utilisateur une description d'une commande.");
      client->send_msg("Syntaxe : /HELP [nom de commande facultatif]");
    }
    else if (cmd == "pass") 
    {
      client->send_msg("La commande PASS permet de se connecter au serveur en saisissant le "
          "mot de passe serveur.");
      client->send_msg("Syntaxe : /PASS <mot de passe>");
    }
    else
      client->send_msg("Desole, nous n'avons pas pu trouver votre commande.");
  }
}
