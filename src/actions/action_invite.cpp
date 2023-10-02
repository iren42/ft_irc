#include "Server.hpp"

void Server::do_action_invite(Client *client, std::vector<std::string> args){
	if (args.size() != 3) {
		client->send_msg("Erreur dans le nombre d'arguments. Format: INVITE user_name channel_name");
		return;}
	
	std::string	user_name = args[1];
	std::string channel_name = args[2];

	std::map<std::string, Channel *>::iterator channel_it = _map_channel.find(channelName);
	if (channel_it == _map_channel.end()) {
		client->send_msg("Le canal" + channelName + "n'existe pas.");
		return;}

	std::map<int, client *>::iterator client_it = _map_client.begin();
	while (client_it != _map_client.end()) {
		if (client_it->second->getNickname() == user_name) {
			Channel *channel = channel_it->second;
			if (channel->is_client(client_it->second)) {
				client->send_msg(user_name + "est déjà dans le canal " + channel_name);}
			else {
				channel->add_client(client_it->second);
				client->send_msg("vous avez invité " + user_name + "à rejoindre le canal" + channel_name);
				client_it->second->send_msg("vous avez été invité à rejoindre le canal" + channel_name);}
			return;}
			++client_it;}
	client->send->msg("L'utilisateur " + user_name + " n'existe pas.");
}
