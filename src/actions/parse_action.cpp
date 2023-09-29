#include "Server.hpp"

void Server::init_map_action()
{
	_map_cmd["nick"] = &Server::do_action_nick;
	_map_cmd["username"] = &Server::do_action_username;
	_map_cmd["join"] = &Server::do_action_join;
	_map_cmd["part"] = &Server::do_action_part;
	_map_cmd["msg"] = &Server::do_action_msg;
	_map_cmd["help"] = &Server::do_action_help;
	_map_cmd["quit"] = &Server::do_action_quit;
	_map_cmd["list"] = &Server::do_action_list;
	_map_cmd["whois"] = &Server::do_action_whois;
	_map_cmd["me"] = &Server::do_action_me;
	_map_cmd["kick"] = &Server::do_action_kick;
	_map_cmd["invite"] = &Server::do_action_invite;
	_map_cmd["topic"] = &Server::do_action_topic;
	_map_cmd["mode"] = &Server::do_action_mode;
}

std::string Server::handle_client(int client_fd)
{
	if (_swtch == 0)	{
		_msg.clear();}
	char tmp[100] = {0};
	int r = recv(client_fd, tmp, 100, 0); //recevoir jusque 100octet de donnée de ckient_fd
	std::cout << "recv = '" << tmp << "'" << std::endl;
	if (r == -1) {
		perror("Error while receiving data.");
		return std::string();}
	else if (r == 0) {
		std::cout << "client disconnection" << std::endl; //GERER LA DISCONNEXION Client
		return std::string();}
		_swtch = 1;
		_msg.append(tmp, r);

		//recherche de la premiere occurence de "\r\n" ou "\n"
		size_t newline = this->_msg.find("\r\n");
		if (newline == std::string::npos) { //npos = find n'a pas trouvé ce qu'il cherchait
			newline = _msg.find("\n");}
		//si une newline est trouvée dans le tampon de msg = msg valide
		if (newline != std::string::npos) {
			_swtch = 0;
			return (_msg);}
		return std::string();
		
}
/*je passe une string vide quand il y a une erreur de recv*/

void Server::parse_action(std::string message, Client *client)
{
//	handle_client(client._fd);
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
