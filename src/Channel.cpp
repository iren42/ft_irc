//
// Created by d420d4 on 16/09/23.
//
#include "Channel.hpp"
#include "Colors.hpp"


const std::string &Channel::getName() const {
    return _name;
}

const std::string &Channel::getTopic() const {
    return _topic;
}

bool Channel::is_client(const Client *client) const {
    for (std::vector<Client *>::const_iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (*it == client) return true;
    }
    return false;
}

bool Channel::is_op(const Client *client) const {
    for (std::vector<Client *>::const_iterator it = _ops.begin(); it != _ops.end(); ++it) {
        if (*it == client) return true;

    }
    return false;
}

size_t Channel::get_nb_clients() const {
    return _clients.size();
}

size_t Channel::get_nb_ops() const {
    return _ops.size();
}

void Channel::setName(const std::string &name) {
    _name = name;
}

void Channel::setTopic(const std::string &topic) {
    _topic = topic;
}

void Channel::add_client(Client *client) {
    if (!is_client(client))
        _clients.push_back(client);

}

void Channel::add_op(Client *client) {
    if (!is_op(client))
        _ops.push_back(client);

}

void Channel::remove_client(Client *client) {
    for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        if (*it == client) {
            _clients.erase(it);
            break;
        }
    }
}

void Channel::remove_op(Client *client) {
    for (std::vector<Client *>::iterator it = _ops.begin(); it != _ops.end(); ++it) {
        if (*it == client) {
            _ops.erase(it);
            break;
        }
    }
}

Channel::Channel(std::string name, Client *creator) : _name(name) {
    _topic = "";
    _clients.push_back(creator);
    _ops.push_back(creator);
}

Channel::Channel(const Channel &other) : _name(other._name), _topic(other._topic),
                                         _clients(other._clients), _ops(other._ops) {
}

Channel &Channel::operator=(const Channel &other) {
    if (this != &other) {  // Vérifier l'auto-affectation.
        _name = other._name;
        _topic = other._topic;
        _clients = other._clients;
        _ops = other._ops;
        // Effectuer des opérations d'affectation personnalisées si nécessaire.
    }
    return *this;
}

Channel::~Channel() {

}