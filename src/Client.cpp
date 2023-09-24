//
// Created by d420d4 on 15/09/23.
//
#include <sys/socket.h>
#include "Client.hpp"
#include "Colors.hpp"

Client::Client() : _fd(-1) {}

Client::Client(std::string hostname, int fd) : _hostname(hostname),_fd(fd) {}

Client::Client(const Client &client) {
    _nickname = client._nickname;
    _realname = client._realname;
    _hostname = client._hostname;
    _username = client._username;
    _fd = client._fd;
}

Client &Client::operator=(const Client &client) {
    if (this != &client) {
        _nickname = client._nickname;
        _realname = client._realname;
        _hostname = client._hostname;
        _username = client._username;
        _fd = client._fd;
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

void Client::send_msg(std::string msg) {

    std::string msg2 = msg + "\r\n";

    if (send(_fd, msg2.c_str(), msg2.length(), 0) < 0)
        throw std::runtime_error("Error while sending message to client.");
}

std::ostream &operator<<(std::ostream &outFile, Client const &client) {
    outFile << BOLDWHITE << "Nickname: " << RESET<< client.getNickname() << std::endl;
    outFile << BOLDWHITE << "Realname: " << RESET<< client.getRealname() << std::endl;
    outFile << BOLDWHITE << "Hostname: " << RESET<< client.getHostname() << std::endl;
    outFile << BOLDWHITE << "File Descriptor: " << RESET<< client.getFd() << std::endl;

    outFile << RESET;

    return outFile;
}