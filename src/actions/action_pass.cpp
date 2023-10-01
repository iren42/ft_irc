#include "Server.hpp"

void Server::do_action_pass(Client *client, std::vector<std::string> args){
  if (args.size() != 2)
  {
    client->send_msg("Syntax error, it should be: '/PASS <password>'");
  }
  else
  {
    if (getPass() == args.back())
    {
      client->setVerified(true);
      client->send_msg("Password verified. You can register your connection, try '/NICK <YourNickname>'");
      // TODO: add condition: /pass must be the 1st cmd to be called
    }
    else
    {
      client->send_msg("Incorrect password. Try again."); 
    }
  }
}
