//
// Created by d420d4 on 16/09/23.
//

#ifndef FT_IRC_CHANNEL_H
#define FT_IRC_CHANNEL_H

#include <string>
#include <iostream>
#include <vector>
#include "Client.hpp"
#include "Server.hpp"

class Channel {
private:
    std::string _name;
    std::string _topic;

    bool _mode_invite;
    bool _mode_topicOp;
    std::string _lockPass;
    int _limit;

    std::vector<Client *> _clients;
    std::vector<Client *> _ops;
    std::vector<Client *> _invite;

public:

    Channel(std::string name, Client *creator);

    Channel(const Channel &client);

    Channel &operator=(const Channel &client);

    virtual ~Channel();


    const std::string &getName() const;

    const std::string &getTopic() const;

    bool is_client(const Client *client) const;

    bool is_op(const Client *client) const;

    bool is_invite(const Client *client) const;

    size_t get_nb_clients() const;

    size_t get_nb_ops() const;

    const std::vector<Client *> &getOps() const;

    const std::vector<Client *> &getClients() const;

    void setName(const std::string &name);

    void setTopic(const std::string &topic);

    bool add_client(Client *client);

    void add_invite(Client *client);

    void add_op(Client *client);

    void remove_client(Client *client);

    void remove_op(Client *client);

    void remove_invite(Client *client);

    bool isEmpty();

    bool isModeInvite() const;

    void setModeInvite(bool modeInvite);

    bool isModeTopicOp() const;

    void setModeTopicOp(bool modeTopicOp);

    const std::string &getLockPass() const;

    void setLockPass(const std::string &lockPass);

    int getLimit() const;

    void setLimit(int limit);

    void replyAll(std::string msg);
};


#endif //FT_IRC_CHANNEL_H
