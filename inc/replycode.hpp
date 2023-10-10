//
// Created by d420d4 on 10/10/23.
//

#ifndef FT_IRC2_REPLYCODE_H
#define FT_IRC2_REPLYCODE_H

#define ERR_NOSUCHNICK(source, target)            "401 " + source + " " + target + " :No such nickname / channel"
#define ERR_NOSUCHCHANNEL(source, target)        "403 " + source + " " + target + " :Channel name is invalid, or does not exist"
#define ERR_CANNOTSENDTOCHAN(source, target)        "404 " + source + " " + target + " :Cannot send a message to channel"
#define ERR_NORECIPIENT(source)            "411 " + source + " :no recipient"
#define ERR_NOTEXTTOSEND(source)            "412 " + source + " :no text to send"
#define ERR_UNKNOWNCOMMAND(source, command)        "421 " + source + " " + command + " :Command unknown"
#define ERR_NONICKNAMEGIVEN(source, command)        "431 " + source + " " + command + " :No new nickname has been given"
#define ERR_ERRONEUSNICKNAME(source)            "432 " + source + " :This nickname is Invalid"
#define ERR_NICKNAMEINUSE(nickname)            "433 " + nickname + " " + nickname + " :Nickname already in use"
#define ERR_USERNOTINCHANNEL(source, target, channel)    "441 " + source + " " + target + " " + channel + " :They aren't on that channel"
#define ERR_NOTONCHANNEL(source, channel)        "442 " + source + " " + channel + " :You're not on that channel"
#define ERR_USERONCHANNEL(source, target, channel)        "443 " + source + " "+target + " " + channel + " : already on channel"
#define ERR_NOTREGISTERED(source)            "451 " + source + " : You have not registered"
#define ERR_NEEDMOREPARAMS(source, command)        "461 " + source + " " + command + " :Not enough parameters"
#define ERR_ALREADYREGISTERED(source)            "462 " + source + " :You may not reregister, you already have!"
#define ERR_PASSWDMISMATCH(source)            "464 " + source + " :Is NOT the correct password for this server."
#define ERR_CHANNELISFULL(source, channel)        "471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN(source, channel)        "473 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_UNKNOWNMODE(source, modechar)        "472 " + source + " " + modechar + " :is unknown char to me"
#define ERR_BADCHANNELKEY(source, channel)        "475 " + source + " " + channel + " :Channel's key is incorrect"
#define ERR_CHANOPRIVSNEEDED(source, channel)        "482 " + source + " " + channel + " :You're not channel creator or operator"


#define RPL_WELCOME(source)                    "001 " + source + " :Bienvenue !!! " + source
#define RPL_CHANNELMODEIS(source, target, modes, params)"324 " + source + " " + target + " " + modes + " " + params
#define RPL_NOTOPIC(source, channel)                "331 " + source + " " + channel + " :No topic is set"
#define RPL_TOPIC(channel, topic)		            "TOPIC " + channel + " " + topic
#define RPL_INVITING(source, nickname, channel)        "341 " + source + " " + nickname + " " + channel
#define RPL_NAMREPLY(source, channel, users)        "353 " + source + " = " + channel + " :" + users
#define RPL_PING(command)                           "PONG :" + command
#define RPL_ENDOFNAMES(source, channel)            "366 " + source + " " + channel + " :End of /NAMES list."
#define RPL_JOIN(channel)                       "JOIN :" + channel
#define RPL_PRIVMSG(target, message)            "PRIVMSG " + target + " :" + message
#define RPL_PART(channel, message)              "PART " + channel + " " + message
#define RPL_NOTICE(target, message)             "NOTICE " + target + " :" + message
#define RPL_NICK(newnick)               "NICK :" + newnick
#define RPL_KICK(channel, target, message)      "KICK " + channel + " " + target + " " + message
#define RPL_QUIT               "QUIT  :"

#endif //FT_IRC2_REPLYCODE_H
