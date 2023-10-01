#include "Server.hpp"

void Server::init_map_action()
{
	_map_cmd["/pass"] = &Server::do_action_pass;
	_map_cmd["/nick"] = &Server::do_action_nick;
	_map_cmd["/username"] = &Server::do_action_username;
	_map_cmd["/join"] = &Server::do_action_join;
	_map_cmd["/part"] = &Server::do_action_part;
	_map_cmd["/privmsg"] = &Server::do_action_privmsg;
	_map_cmd["/help"] = &Server::do_action_help;
	_map_cmd["/quit"] = &Server::do_action_quit;
	_map_cmd["/list"] = &Server::do_action_list;
	_map_cmd["/whois"] = &Server::do_action_whois;
	_map_cmd["/me"] = &Server::do_action_me;
	_map_cmd["/kick"] = &Server::do_action_kick;
	_map_cmd["/invite"] = &Server::do_action_invite;
	_map_cmd["/topic"] = &Server::do_action_topic;
	_map_cmd["/mode"] = &Server::do_action_mode;
}
void Server::parse_action(std::string message, Client *client)
{
	std::string firstWord = message.substr(0, message.find(' '));
	for (int i = 0; i < firstWord.length(); i++)
		firstWord.at(i) = (char) std::tolower(firstWord.at(i));

	std::vector<std::string> arguments;
	std::string motActuel;

	//TODO a ameliorer avec les fonctions cpp
	for (int i = 0; i < message.length(); i++)
		if (message.at(i) != ' ')
			motActuel += message.at(i);
		else if (!motActuel.empty())
		{
			arguments.push_back(motActuel);
			motActuel.clear();
		}

	if (!motActuel.empty())
		arguments.push_back(motActuel);
	
	if (_map_cmd.find(firstWord) != _map_cmd.end())
		((this->*_map_cmd[firstWord]))(client, arguments);
	else
	{
		std::cout << "Not a command" << std::endl;
	}
}
