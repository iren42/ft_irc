//
// Created by d420d4 on 15/09/23.
//
#ifndef FT_IRC_CLIENT_H
#define FT_IRC_CLIENT_H

#include <iostream>
#include <string>

class Client {
private:
  std::string _nickname;
  std::string _realname;
  std::string _hostname;
  std::string _username;
  int _fd;
//  Server *_serv;
  bool  _verified;
   

  Client();

public:
  Client(std::string hostname, int fd);
  Client(const Client &client);
  Client &operator=(const Client &client);
  virtual ~Client();

  const std::string &getNickname() const;
  const std::string &getRealname() const;
  const std::string &getHostname() const;
  const std::string &getUsername() const;
  int getFd() const;
 // Server* getServer() const;
  bool  isVerified() const;

  void setNickname(const std::string &nickname);
  void setRealname(const std::string &realname);
  void setHostname(const std::string &hostname);
  void setUsername(const std::string &hostname);
  void setVerified(bool);
  void setFd(int fd);

  void send_msg(std::string msg);
};

std::ostream &operator<<(std::ostream &outFile, Client const &client);

#endif // FT_IRC_CLIENT_H
