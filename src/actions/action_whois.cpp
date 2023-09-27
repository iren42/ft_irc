#include "Server.hpp"

void Server::do_action_whois(Client *client, std::vector<std::string> args) {
  if (args.size() != 2)
  {
    client->send_msg(
        "Error: syntax should be: '/WHOIS <nick>'\nFor example, '/WHOIS john'");
  }
  else
  {
    std::string nick = args.back();
	CLIENTS map = client->getServer()->getClients();
	CLIENTS::iterator it = map.begin();
	while (it != map.end())
	{
		if (((*it).second)->getNickname() == nick)
		{
			std::cout << "nick found" << std::endl;
			// TODO display info about nick
		}
		it++;
	}
  }
}
