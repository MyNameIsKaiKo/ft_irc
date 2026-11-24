/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 02:26:55 by jleray            #+#    #+#             */
/*   Updated: 2026/11/18 16:49:00 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message()
{
	this->clientFd = -1;
}

Message::Message(const Message& other)
{
	*this = other;
}

Message& Message::operator=(const Message& other)
{
	if (this != &other)
	{
		this->clientFd = other.clientFd;
		this->prefix = other.prefix;
		this->command = other.command;
		this->params = other.params;
	}
	return (*this);
}

void	Message::setClientFd(const int cFd)
{
	this->clientFd = cFd;
}

void	Message::setPrefix(const std::string pref)
{
	this->prefix = pref;
}

void	Message::setCommand(const std::string com)
{
	this->command = com;
}

void	Message::setParams(const std::vector<std::string> params)
{
	this->params = params;
}

int		Message::getClientFd(void)
{
	return (this->clientFd);
}

std::string	Message::getPrefix(void)
{
	return (this->prefix);
}

std::string Message::getCommand(void)
{
	return (this->command);
}

std::vector<std::string> Message::getParams(void)
{
	return (this->params);
}

Message::~Message()
{

}
