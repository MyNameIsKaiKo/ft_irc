#pragma once

// error messages
# define ERR_PASSWDMISMATCH(client) std::string(":" + SERVNAME + " 464 " + client.getNickname() + " :Invalid Password\r\n")
# define ERR_NICKNAMEINUSE(client) std::string(":" + SERVNAME + " 433 " + client.getNickname() + " :This nickname is already in use on the network\r\n")
# define ERR_ERRONEUSNICKNAME(client) std::string(":" + SERVNAME + " 432 " + client.getNickname() + " :There is at least an invalid charactere\r\n")
# define ERR_NONICKNAMEGIVEN std::string(":" + SERVNAME + " 431 " + ":The <nickname> parameter was not received\r\n")
# define ERR_ALREADYREGISTERED std::string(":" + SERVNAME + " 462 " + ":Once registration is complete, you can no longer use the USER command\r\n")
# define ERR_NOTREGISTERED(client) std::string(":" + SERVNAME + " 451 " + client.getNickname() + " :You have not register\r\n")

//other messages
# define SETNICKNAME(client, lastNickname) std::string(":" + SERVNAME + " " + lastNickname + " changed his nickname to " + client.getNickname() + "\r\n")
# define WELCOME std::string(":" + SERVNAME + " :Welcome in this server\r\n")
# define DEFAULTREALUSERNAME std::string(":Your username and realname have been set by default to your nickname\r\n")
# define SETREALUSERNAME(client) std::string(":" + SERVNAME + " your username is " + client.getUsername() + " your realname is " + client.getRealname() + "\r\n")