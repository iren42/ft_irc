#include "Server.hpp"

void Server::do_action_whois(Client *client, std::vector<std::string> args)
{
  if (args.size() != 2)
  {
    client->send_msg(
        "Error: syntax should be: '/WHOIS <nick>'\nFor example, '/WHOIS john'");
  }
  else
  {
    std::string nick = args.back();
    std::string buf;
    CLIENTS map = client->getServer()->getClients();
    CLIENTS::iterator it = map.begin();
    /*
     * Write this message on the client side:
     * <nick> is <username>
     * <nick> on <channels>
     */
    while (it != map.end())
    {
      if (((*it).second)->getNickname() == nick)
      {
        buf.append(nick);
        buf.append(" is ");
        buf.append((*it).second->getUsername());
        buf.append("\n");
        buf.append(nick);
        buf.append(" on");
        CHANNELS chan = (*it).second->getServer()->getChannels();
        CHANNELS::iterator ita = chan.begin();
        while (ita != chan.end())
        {
          if (((*ita).second)->is_client((*it).second))
          {
            buf.append(" #");
            buf.append((*ita).first);
          }
          ita++;
        }
      }
      it++;
    }
    client->send_msg(buf);
  }
}
