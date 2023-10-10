//
// Created by d420d4 on 15/09/23.
//
#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#define LENGTH_MSG 8192

#include <iostream>
#include <string>
#include <functional>
#include <ctime>
#include <iostream>
#include <sstream>

class Server;

class Client {
private:
    std::string _nickname;
    std::string _realname;
    std::string _hostname;
    std::string _username;
    std::string _msg;
    int _fd;
    Server *_serv;
    bool _verified;
    int _swtch;


    std::string generateRandomColor(const std::string &seed);

    unsigned int strhash(const char *str);

    Client();

public:
    Client(std::string hostname, int fd, Server *);

    Client(const Client &client);

    Client &operator=(const Client &client);

    virtual ~Client();

    const std::string &getNickname() const;

    const std::string &getRealname() const;

    const std::string &getHostname() const;

    const std::string &getUsername() const;

    int getFd() const;

    Server *getServer() const;

    bool isVerified() const;

    bool isNickSet() const;

    void setNickname(const std::string &nickname);

    void setRealname(const std::string &realname);

    void setHostname(const std::string &hostname);

    void setUsername(const std::string &hostname);

    void setVerified(bool);

    void setFd(int fd);

    void send_msg(std::string msg);

    void send_brut(std::string msg);

    void reply(std::string msg);

    std::string getPrefix();

    void send_msg(std::string msg, std::string sender);

    void disconnect();

    int get_swtch();

    void swtch_on();

    void swtch_off();

    std::string &get_msg();
};

std::ostream &operator<<(std::ostream &outFile, Client const &client);

#endif // FT_IRC_CLIENT_H
