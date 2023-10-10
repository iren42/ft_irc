//
// Created by d420d4 on 16/09/23.
//
#include "Channel.hpp"
#include "Colors.hpp"

bool Channel::is_client(const Client *client) const
{
	for (std::vector<Client *>::const_iterator it = _clients.begin();
		 it != _clients.end(); ++it)
		if (*it == client) return true;

	return false;
}

bool Channel::is_op(const Client *client) const
{
	for (std::vector<Client *>::const_iterator it = _ops.begin();
		 it != _ops.end(); ++it)
		if (*it == client) return true;

	return false;
}

bool Channel::is_invite(const Client *client) const
{
	for (std::vector<Client *>::const_iterator it = _invite.begin();
		 it != _invite.end(); ++it)
		if (*it == client) return true;

	return false;
}

size_t Channel::get_nb_clients() const
{
	return _clients.size();
}

size_t Channel::get_nb_ops() const
{
	return _ops.size();
}

void Channel::setName(const std::string &name)
{
	_name = name;
}

void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
}

bool Channel::add_client(Client *client)
{
	if (get_nb_clients() >= static_cast<size_t>(_limit) && _limit > 0)
	{
		client->reply(ERR_CHANNELISFULL(client->getNickname(), _name));
		return false;
	}

	if (_mode_invite && !is_invite(client))
	{
		client->reply(ERR_INVITEONLYCHAN(client->getNickname(), _name));
		return false;
	}

	if (_mode_invite)
		remove_invite(client);

	if (!is_client(client))
	{
		_clients.push_back(client);
		return true;
	}
	return false;

}


void Channel::add_invite(Client *client)
{

	if (is_invite(client))
		return;

	_invite.push_back(client);
}


void Channel::add_op(Client *client)
{
	if (!is_op(client))
		_ops.push_back(client);

}

void Channel::remove_client(Client *client)
{
	for (std::vector<Client *>::iterator it = _clients.begin();
		 it != _clients.end(); ++it)
	{
		if (*it == client)
		{
			_clients.erase(it);
			break;
		}
	}
	remove_op(client);
}

void Channel::remove_op(Client *client)
{
	for (std::vector<Client *>::iterator it = _ops.begin();
		 it != _ops.end(); ++it)
	{
		if (*it == client)
		{
			_ops.erase(it);
			break;
		}
	}
	if (_ops.empty() && !_clients.empty())
	{
		_clients[0]->send_msg("Plus d'op sur le canal " + getName() +
							  ". Vous avez été nommé op par défaut.");
		_clients[0]->getServer()->send_all(
				client->getPrefix() + " MODE " + getName() + " +o " +
				_clients[0]->getNickname() + "\r\n");
		_ops.push_back(_clients[0]);
	}
}

void Channel::remove_invite(Client *client)
{
	for (std::vector<Client *>::iterator it = _invite.begin();
		 it != _invite.end(); ++it)
	{
		if (*it == client)
		{
			_invite.erase(it);
			break;
		}
	}
}


Channel::Channel(std::string name, Client *creator) : _name(name)
{
	_mode_invite = false;
	_mode_topicOp = true;
	_lockPass = "";
	_limit = -1;
	_topic = "";
	_clients.push_back(creator);
	_ops.push_back(creator);
}

Channel::Channel(const Channel &other) : _name(other._name),
										 _topic(other._topic),
										 _clients(other._clients),
										 _ops(other._ops)
{
}

Channel &Channel::operator=(const Channel &other)
{
	if (this != &other)
	{  // Vérifier l'auto-affectation.
		_name = other._name;
		_topic = other._topic;
		_clients = other._clients;
		_ops = other._ops;
		// Effectuer des opérations d'affectation personnalisées si nécessaire.
	}
	return *this;
}

Channel::~Channel()
{

}

bool Channel::isEmpty()
{
	return _clients.empty();
}

const std::vector<Client *> &Channel::getClients() const
{
	return _clients;
}

const std::vector<Client *> &Channel::getOps() const
{
	return _ops;
}

const std::string &Channel::getName() const
{
	return _name;
}

const std::string &Channel::getTopic() const
{
	return _topic;
}

bool Channel::isModeInvite() const
{
	return _mode_invite;
}

void Channel::setModeInvite(bool modeInvite)
{
	_mode_invite = modeInvite;
}

bool Channel::isModeTopicOp() const
{
	return _mode_topicOp;
}

void Channel::setModeTopicOp(bool modeTopicOp)
{
	_mode_topicOp = modeTopicOp;
}

const std::string &Channel::getLockPass() const
{
	return _lockPass;
}

void Channel::setLockPass(const std::string &lockPass)
{
	_lockPass = lockPass;
}

int Channel::getLimit() const
{
	return _limit;
}

void Channel::setLimit(int limit)
{
	_limit = limit;
}

void Channel::replyAll(std::string msg)
{
	for (std::vector<Client *>::iterator it = _clients.begin();
		 it != _clients.end(); ++it)
	{
		(*it)->send_brut(msg + "\r\n");
	}
}
