/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 02:26:55 by jleray            #+#    #+#             */
/*   Updated: 2026/11/18 02:59:36 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message()
{

}

Message::Message(const Message& other)
{
	*this = other;
}

Message& Message::operator=(const Message& other)
{
	if (this != &other)
	{
		this.clientFd = other->clientFd;
		this.prefix = other->prefix;
		this.command = other->command;
		this.params = other->params;
	}
	return (*this);
}

Message::~Message()
{

}
