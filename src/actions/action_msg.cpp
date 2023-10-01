#include "Server.hpp"

// removes the 1st char of s if it is a '#', it corresponds to the prefix of a channel
std::string Server::parseChannel(std::string s)
{
  if (s.size() > 1)
  {
    if (s.at(0) == '#')
    {
      std::string channel = s.substr(1, s.size() - 1);
      return (channel);
    }
  }
  return (s);
}

bool  Server::isInMapChannel(std::string s)
{
  std::string chan = parseChannel(s);
  CHANNELS::iterator it = _map_channel.find(chan);
  if (it != _map_channel.end())
    return (true);
  return (false);
}

// send a message to every client that joined the channel <recipient>
// TODO send a message only when sender has joined that channel,
// or if that channel is not in mode -n
void	Server::msgChannel(Client *sender, std::string recipient, std::vector<std::string> args)
{
  // find Channel*
  CHANNELS::iterator it = _map_channel.find(parseChannel(recipient));
  if (it != _map_channel.end())
  {
    std::vector<Client *> vec =  (((*it).second)->getClients());
    std::vector<Client *>::iterator ita = vec.begin();
    while (ita != vec.end())
    {
      (*ita)->send_msg("[" + recipient + "] " + sender->getNickname() + ": " + createMsg(args));
      ita++;
    }
  }
}

// returns an iterator to the element with <nick> on success 
// returns _map_client.end() on failure
CLIENTS::iterator Server::findClient(std::string nick)
{
  CLIENTS::iterator it = _map_client.begin();
  while (it != _map_client.end())
  {
    if (((*it).second)->getNickname() == nick)
    {
      return (it);
    }
    it++;
  }
  return (it);
}

// concatenate every string after the '/CMD <recipient>' with a ' '
std::string Server::createMsg(std::vector<std::string> args)
{
  std::string buf;
  std::vector<std::string>::iterator ita = args.begin();
  ita += 2;
  while (ita != args.end())
  {
    buf.append(*ita);
    buf.append(" ");
    ita++;
  }
  return (buf);
}

// send a message to a Client
void	Server::msgClient(Client *sender, std::string recipient, std::vector<std::string> args)
{
  CLIENTS::iterator receiver = findClient(recipient);
  if (receiver != _map_client.end())
  {
    ((*receiver).second)->send_msg(sender->getNickname() + ": " + createMsg(args));
  }
  else {
    sender->send_msg("ERR_NOSUCHNICK");
  }
}

void Server::do_action_msg(Client *sender, std::vector<std::string> args)
{
  if (args.size() == 1)
  {
    sender->send_msg("ERR_NORECIPIENT");
  }
  else if (args.size() == 2)
  {
    sender->send_msg("ERR_NOTEXTTOSEND");
  }
  else
  {
    // case 1: recipient has '#' as the 1st char, it may be an existing channel
    if (args.at(1).at(0) == '#')
    {
      if (isInMapChannel(args.at(1)))
      {
        msgChannel(sender, args.at(1), args);
      }
      else {
        sender->send_msg("Nous n'avons pas trouvé le canal : " + args.at(1));
      }
    }
    // case 2: recipient is a client
    else {
      msgClient(sender, args.at(1), args);
    }
  }
}
