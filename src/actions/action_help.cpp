#include "Server.hpp"

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
    client->send_msg("Syntaxe : /HELP [nom de la commande]\n"
        "Par exemple, '/HELP NICK'");
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
          "[<cle>].\nNotre liste de canaux est disponible avec la commande /LIST\n"
          "Vous ne savez plus par ou commencer ? Essayez '/HELP PASS'");
    }
    else if (cmd == "nick")
    {
      client->send_msg("Changez le surnom sous lequel vous etes connu.\nLes surnoms sont limites a 9 caracteres.\n"
          "Syntaxe : /NICK <VotreSurnom>");
    }
    else if (cmd == "user") 
    {
      client->send_msg(
          "Cette commande est utilisee au debut d'une connexion pour specifier "
          "le nom d'utilisateur, le nom d'hote et le nom reel du client connecte\n"
          "Syntaxe : /USER <nom d'utilisateur> <nom d'hote> <nom reel>");
    }
    else if (cmd == "join") 
    {
      client->send_msg(
          "Permet a un utilisateur de rejoindre le canal specifie.\n"
          "Si le canal n'existe pas encore, il sera cree et vous en serez l'operateur\n"
          "Syntaxe : /JOIN <canal> [<cle>]");
    }
    else if (cmd == "part") 
    {
      client->send_msg("Permet a un utilisateur de quitter un canal\n"
          "Syntaxe : /PART <canal> [<message>]");
    } 
    else if (cmd == "privmsg") 
    {
      client->send_msg(
          "Envoie un message privee a <surnom>.\n"
          "Syntaxe : /MSG <surnom | canal> <message>\nPar exemple, '/PRIVMSG John Salut John'"
          "\n/PRIVMSG #unCanal Salut les membres de unCanal !");
    } 
    else if (cmd == "quit") 
    {
      client->send_msg("Quitte IRC (et quitte egalement tous les canaux auxquels vous pourriez etre connecte).\n"
          "Syntaxe : /QUIT [message d'adieu facultatif]");
    }
    else if (cmd == "list")
    {
      client->send_msg(
          "Affiche la liste des canaux IRC, le nombre d'utilisateurs et le sujet de chacun.\n"
          "Syntaxe : /LIST");
    }
    else if (cmd == "whois") 
    {
      client->send_msg("Affiche des informations sur le surnom specifie.\n"
          "Syntaxe : /WHOIS <surnom>");
    }
    else if (cmd == "me") 
    {
      client->send_msg("Affiche un message en rose dans un canal.\n"
          "Syntaxe : /ME <message>\nPar exemple, '/ME chante Here Comes The Sun - The Beatles'");
    }
    else if (cmd == "kick") 
    {
      client->send_msg("Retire de force un utilisateur d'un canal. "
          "Cette commande ne peut etre utilisee que par un operateur de canal.\n"
          "Syntaxe : /KICK <canal> <utilisateur> [<commentaire>]");
    }
    else if (cmd == "invite") 
    {
      client->send_msg("Invite <surnom> dans le canal <canal>. <canal> n'a pas besoin d'exister, "
          "mais si c'est le cas, seuls les membres du canal sont autorises a inviter de nouveaux membres.\n"
          "Syntaxe : /INVITE <surnom> <canal>");
    }
    else if (cmd == "topic") 
    {
      client->send_msg(
          "La commande TOPIC est utilisee pour changer ou afficher le sujet d'un canal. "
          "Le sujet du canal <canal> est renvoye s'il n'y a pas de <sujet> donne. "
          "Si le parametre <sujet> est present, le sujet du canal sera modifie, "
          "si les modes du canal le permettent.\n"
          "Syntaxe : /TOPIC <canal> [<sujet>]");
    }
    else if (cmd == "mode") 
    {
      client->send_msg("La commande MODE est polyvalente. Elle peut etre utilisee pour definir "
          "a la fois les modes utilisateur et les modes de canal.\n"
          "Syntaxe : /MODE <canal> <drapeaux> [<arguments>]\n"
          "/MODE <surnom> <drapeaux> (utilisateur)");
    }
    else if (cmd == "help") 
    {
      client->send_msg(
          "La commande HELP affiche a un utilisateur une description d'une commande.\n"
          "Syntaxe : /HELP [nom de commande facultatif]");
    }
    else if (cmd == "pass") 
    {
      client->send_msg("La commande PASS permet de se connecter au serveur en saisissant le "
          "mot de passe serveur.\n"
          "Syntaxe : /PASS <mot de passe>");
    }
    else
      client->send_msg("Desole, nous n'avons pas pu trouver votre commande.");
  }
}
