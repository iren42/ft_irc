//
// Created by d420d4 on 15/09/23.
//
#include <sys/socket.h>
#include "Client.hpp"
#include "Colors.hpp"
#include "Server.hpp"

Client::Client() : _fd(-1) {}

Client::Client(std::string hostname, int fd, Server *s) : _hostname(hostname), _fd(fd), _serv(s), _verified(false) {
    _nickname = "";
    _realname = "";
    _username = "";
    _msg = "";
    _swtch = 0;
}

Client::Client(const Client &client) {
    _nickname = client._nickname;
    _realname = client._realname;
    _hostname = client._hostname;
    _username = client._username;
    _fd = client._fd;
    _verified = client._verified;
}

Client &Client::operator=(const Client &client) {
    if (this != &client) {
        _nickname = client._nickname;
        _realname = client._realname;
        _hostname = client._hostname;
        _username = client._username;
        _fd = client._fd;
        _verified = client._verified;
    }
    return *this;
}

Client::~Client() {

}

const std::string &Client::getNickname() const {
    return _nickname;
}

const std::string &Client::getRealname() const {
    return _realname;
}

const std::string &Client::getHostname() const {
    return _hostname;
}

const std::string &Client::getUsername() const {
    return _username;
}


int Client::getFd() const {
    return _fd;
}

bool Client::isVerified() const {
    return (_verified);
}

bool Client::isNickSet() const {
    return (_nickname != "");
}

Server *Client::getServer() const {
    return (_serv);
}

void Client::setNickname(const std::string &nickname) {
    _nickname = nickname;
}

void Client::setRealname(const std::string &realname) {
    _realname = realname;
}

void Client::setHostname(const std::string &hostname) {
    _hostname = hostname;
}

void Client::setUsername(const std::string &username) {
    _username = username;
}

void Client::setFd(int fd) {
    _fd = fd;
}

void Client::setVerified(bool value) {
    _verified = value;
}

void Client::send_msg(std::string msg) {
    send_msg(msg, "Serveur");
}

std::string Client::getPrefix() {
    return ":" + _nickname + "!" + _username + "@" + _hostname;
}

void Client::reply(std::string msg) {

    std::string msg2 = getPrefix() + " " + msg;
    send_brut(msg2 + "\r\n");
}

void Client::send_brut(std::string msg) {
    if (send(_fd, msg.c_str(), msg.length(), 0) < 0) {
        throw std::runtime_error("Erreur lors de l'envoi du message au client.");
    } else
        std::cout << "Message sent :" << msg << std::endl;
}


unsigned int Client::strhash(const char *str) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}


std::string Client::generateRandomColor(const std::string &seed) {
    std::srand(strhash(seed.c_str()));

    int color = std::rand() % 7 + 31;

    std::stringstream colorCode;
    colorCode << "\033[1;" << color << "m";
    return colorCode.str();
}

void Client::send_msg(std::string msg, std::string sender) {

    if (sender.length() > 12)
        sender = sender.substr(0, 12);

    std::string colorCode = generateRandomColor(sender);
    std::string formattedMsg;
    size_t pos = 0;
    while (pos < msg.length()) {
        size_t newlinePos = msg.find('\n', pos);
        if (newlinePos != std::string::npos) {
            formattedMsg += msg.substr(pos, newlinePos - pos + 1) + std::string(16, ' ');
            pos = newlinePos + 1;
        } else {
            formattedMsg += msg.substr(pos);
            break;
        }
    }

    char messageWithSender[LENGTH_MSG];
    std::string format = "[" + colorCode + "%-12s\033[0m]: %s\r\n";
    snprintf(messageWithSender, sizeof(messageWithSender), format.c_str(), sender.c_str(), formattedMsg.c_str());

    send_brut(messageWithSender);

}

void Client::disconnect() {
    _serv->disconnect(this);
}

std::ostream &operator<<(std::ostream &outFile, Client const &client) {
    outFile << BOLDWHITE << "Nickname: " << RESET << client.getNickname() << std::endl;
    outFile << BOLDWHITE << "Realname: " << RESET << client.getRealname() << std::endl;
    outFile << BOLDWHITE << "Hostname: " << RESET << client.getHostname() << std::endl;
    outFile << BOLDWHITE << "File Descriptor: " << RESET << client.getFd() << std::endl;

    outFile << RESET;

    return outFile;
}

std::string &Client::get_msg() { return (this->_msg); }

int Client::get_swtch() { return (_swtch); }

void Client::swtch_on() { _swtch = 1; }

void Client::swtch_off() { _swtch = 0; }
