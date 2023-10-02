//
// Created by d420d4 on 16/09/23.
//

#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include <string>
#include <iostream>
#include <vector>
#include "Client.hpp"

class Channel {
private:
    std::string _name;
    std::string _topic;

    std::vector<Client *> _clients;
    std::vector<Client *> _ops;

public:

    Channel(std::string name, Client *creator);

    Channel(const Channel &client);

    Channel &operator=(const Channel &client);

    virtual ~Channel();


    const std::string &getName() const;

    const std::string &getTopic() const;

    bool is_client(const Client *client) const;

    bool is_op(const Client *client) const;

    size_t get_nb_clients() const;

    size_t get_nb_ops() const;

    const std::vector<Client *> &getOps() const;

    const std::vector<Client *> &getClients() const;

    void setName(const std::string &name);

    void setTopic(const std::string &topic);

    void add_client(Client *client);

    void add_op(Client *client);

    void remove_client(Client *client);

    void remove_op(Client *client);

    bool isEmpty();
};


#endif //FT_IRC_CHANNEL_H
