/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldepenne <ldepenne@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 19:58:42 by ldepenne          #+#    #+#             */
/*   Updated: 2026/11/25 11:12:00 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include <map>
# include "Client.hpp"
# include "Message.hpp"
# include <sys/socket.h>
# include <cstring>

# define SERVNAME std::string("localhost")

// error messages
# define ERR_PASSWDMISMATCH(client) std::string(":" + SERVNAME + " 464 " + client.getNickname() + " :Invalid Password\r\n")
# define ERR_NICKNAMEINUSE(client) std::string(":" + SERVNAME + " 433 " + client.getNickname() + " :This nickname is already in use on the network\r\n")
# define ERR_ERRONEUSNICKNAME(client) std::string(":" + SERVNAME + " 432 " + client.getNickname() + " :There is at least an invalid charactere\r\n")
# define ERR_NONICKNAMEGIVEN std::string(":" + SERVNAME + " 431 " + ":The <nickname> parameter was not received\r\n")
# define ERR_ALREADYREGISTERED std::string(":" + SERVNAME + " 462 " + ":Once registration is complete, you can no longer use the USER command\r\n")
# define ERR_NOTREGISTERED(client) std::string(":" + SERVNAME + " 451 " + client.getNickname() + " :You have not register\r\n")

//other messages
# define SETNICKNAME(client, lastNickname) std::string(":" + SERVNAME + " " + lastNickname + " changed his nickname to " + client.getNickname() + "\r\n")
# define GOODPASSWD std::string(":" + SERVNAME + " :Welcome in this server\r\n")
# define DEFAULTREALUSERNAME std::string(":Your username and realname have been set by default to your nickname\r\n")
# define SETREALUSERNAME(client) std::string(":" + SERVNAME + " your username is " + client.getUsername() + " your realname is " + client.getRealname() + "\r\n")

class Commands
{
	public:
		static void	Pass(Client &client, const std::string& passwrd, const std::string& servPasswrd);
		static void	Nick(Client &client, const std::string& nickname, const std::map<int, Client>& clients);
		static void	User(Client &client, const std::string& username, const std::string& realname);
};

void	dispatchCommand(Message& msg, Client& client, const std::string& servPassword, const std::map<int, Client>& clients);
void	ft_send(const int& fd, const std::string& msg);

#endif
