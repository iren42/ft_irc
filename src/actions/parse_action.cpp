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

/*void	Server::handle_client(int client_fd)
{
	char tmp[100] = {0};
	int r = recv(client_fd, tmp, 100, 0); //recevoir jusque 100 octet de données de Client_fd
	std::cout << "recv = '" << tmp << "'" << std::endl;
	if (r == -1) {
		perror("Error while receiving data.")
		return;}
	else if (r == 0) { //si r = 0 alors il n'ya pas/plus de connexion
		client_disconnect(client_fd, _epollfd); //CLIENT DISCONNEXION
		return;}
	_map_client[client_fd]->getMsg().append(tmp, r);//ajoute les données recue 'tmp' a r.
	size_t newLine = _map_client[client_fd]->getMs().find("\r\n");
	if (newLine == std::string::npos) { //npos = une constante speciale qui dit que find n'a pas trouvé ce qu'il cherchait
		newline = _map_client[client_fd]->getMsg().find("\n");}
	if (newLine !=std::string::npos){
		std::string message = _map_client[client_fd]->getMsg().substr(0, newLine);
		execMsg(_map_client[client_fd], message);}
	
	//supprimer la partie du message traitée
}*/

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
