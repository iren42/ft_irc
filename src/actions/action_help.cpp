#include "Server.hpp"

void Server::do_action_help(Client *client, std::vector<std::string> args) {
  if (args.size() == 1) {
    client->send_msg("*** Liste de toutes les commandes IRC :\n*** NICK, USER, "
                     "JOIN, PART, QUIT, LIST, WHOIS,\n*** PASS, KICK, "
                     "INVITE, TOPIC, MODE, NAMES, NOTICE\nEtes-vous "
                     "un nouvel utilisateur ? Essayez /HELP intro");
  } else if (args.size() > 2) {
    client->send_msg("Syntaxe : /HELP [nom de la commande]\n"
                     "Par exemple, 'HELP NICK'");
  } else {
    std::string cmd = args.back();
    if (cmd == "intro") {
      client->send_msg(
          "Bienvenue sur notre serveur IRC !\nIRC (Internet Relay Chat) est un "
          "systeme de discussion multi-utilisateurs et multi-canaux. C'est "
          "totalement gratuit !\nPour commencer a discuter, "
          "vous devez enregistrer votre connexion avec /NICK (et "
          "/USER). Voir /HELP NICK. "
          "Ensuite, vous pourrez rejoindre un canal de discussion avec /JOIN "
          "<canal> [<cle>].\nNotre liste de canaux est disponible avec la "
          "commande /LIST\n"
          "Vous ne savez plus par ou commencer ? Essayez /HELP NICK");
    } else if (cmd == "nick") {
      client->send_msg(
          "La commande NICK change le nickmame sous lequel vous etes connu.\nLes "
          "nickmames sont limites a 9 caracteres.\n"
          "Syntaxe : /NICK <VotreSurnom>");
    } else if (cmd == "user") {
      client->send_msg(
          "La commande USER est utilisee au debut d'une connexion pour "
          "specifier le nom d'utilisateur, le nom d'hote et le nom reel du "
          "client connecte.\n"
          "Syntaxe : /USER <nom d'utilisateur> <nom d'hote> <nom reel>");
    } else if (cmd == "join") {
      client->send_msg(
          "La commande JOIN permet a un utilisateur de rejoindre le canal "
          "specifie.\n"
          "Si le canal n'existe pas encore, il sera cree et vous en serez "
          "l'operateur\n"
          "Syntaxe : /JOIN <canal> [<cle>]");
    } else if (cmd == "part") {
      client->send_msg(
          "La commande PART permet a un utilisateur de quitter un canal\n"
          "Syntaxe : /PART <canal> [<message>]");
    } else if (cmd == "privmsg") {
      client->send_msg(
          "La commande PRIVMSG envoie un message prive a <nickmame>.\n"
          "Syntaxe : /PRIVMSG <surnom | canal> <message>\nPar "
          "exemple, 'PRIVMSG John Salut John'"
          "\n/PRIVMSG #unCanal Salut les membres de unCanal !");
    } else if (cmd == "quit") {
      client->send_msg("La commade QUIT permet de quitter IRC (et quitte "
                       "egalement tous les canaux "
                       "auxquels vous pourriez etre connecte).\n"
                       "Syntaxe : /QUIT [message d'adieu facultatif]");
    } else if (cmd == "list") {
      client->send_msg(
          "La commade LIST affiche la liste des canaux IRC, le nombre "
          "d'utilisateurs et le sujet de chacun.\n"
          "Syntaxe : /LIST");
    } else if (cmd == "whois") {
      client->send_msg(
          "La commande WHOIS affiche des informations sur le surnom specifie.\n"
          "Syntaxe : /WHOIS <surnom>");
    } else if (cmd == "kick") {
      client->send_msg(
          "La commande KICK retire de force un utilisateur d'un canal. "
          "Cette commande ne peut etre utilisee que par un "
          "operateur de canal.\n"
          "Syntaxe : /KICK <canal> <utilisateur> [<commentaire>]");
    } else if (cmd == "invite") {
      client->send_msg("La commande INVTE invite <surnom> dans le canal "
                       "<canal>. <canal> n'a pas besoin d'exister, mais si "
                       "c'est le cas, seuls les membres du canal sont "
                       "autorises a inviter de nouveaux membres.\n"
                       "Syntaxe : /INVITE <surnom> <canal>");
    } else if (cmd == "topic") {
      client->send_msg("La commande TOPIC est utilisee pour changer ou "
                       "afficher le sujet d'un canal. "
                       "Le sujet du canal <canal> est renvoye s'il n'y a pas "
                       "de <sujet> donne. "
                       "Si le parametre <sujet> est present, le sujet du canal "
                       "sera modifie, si les modes du canal le permettent.\n"
                       "Syntaxe : /TOPIC <canal> [<sujet>]");
    } else if (cmd == "mode") {
      client->send_msg(
              "La commande MODE est polyvalente. Elle peut être utilisée pour "
              "définir à la fois les modes utilisateur et les modes de canal.\n"
              "Syntaxe : /MODE <canal> <drapeaux> [<arguments>] (pour les canaux)\n\n"
              "Modes de canal disponibles :\n"
              "  +l <limite> : Définir la limite du canal à <limite> (utilisez -l pour supprimer la limite).\n"
              "  +k <mdp> : Définir un mot de passe pour le canal (utilisez -k pour retirer le mot de passe).\n"
              "  +i : Activer le mode invité (seuls les opérateurs peuvent inviter de nouveaux utilisateurs, utilisez "
              "-i pour désactiver).\n"
              "  +t : Activer le mode topic op (seuls les opérateurs peuvent modifier le sujet, utilisez -t pour désactiver).\n"
              "  +o <nickname> : Donner le statut d'opérateur à un utilisateur sur le canal.\n"
              "  -o <nickname> : Retirer le statut d'opérateur à un utilisateur sur le canal.");
    } else if (cmd == "help") {
      client->send_msg("La commande HELP affiche a un utilisateur une "
                       "description d'une commande.\n"
                       "Syntaxe : /HELP [nom de commande facultatif]");
    } else if (cmd == "pass") {
      client->send_msg(
          "La commande PASS permet de se connecter au serveur en saisissant le "
          "mot de passe serveur.\n"
          "Syntaxe : /PASS <mot de passe>");
    } else if (cmd == "names") {
      client->send_msg("La commande NAMES permet de lister tous les surnoms "
                       "visibles pour lui.\n"
                       "Syntaxe : /NAMES [<canal>]");
    } else if (cmd == "notice") {
      client->send_msg(
          "La commande NOTICE est utilisee de la meme maniere que PRIVMSG. La "
          "difference entre NOTICE et PRIVMSG est que les reponses "
          "automatiques ne doivent jamais etre envoyees en reponse a un "
          "message NOTICE. Cette regle s'applique aussi aux serveurs.\n"
          "Syntaxe : /NOTICE <surnom | canal> <message>");
    } else
      client->send_msg("Desole, nous n'avons pas pu trouver votre commande.");
  }
}
