/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:23:36 by jleray            #+#    #+#             */
/*   Updated: 2026/11/25 08:42:16 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

static	void show_content(Message msg)
{
	std::cout << msg.getClientFd() << std::endl;
	std::cout << msg.getPrefix() << std::endl;
	std::cout << msg.getCommand() << std::endl;
	std::vector<std::string> params = msg.getParams();
	for (size_t i = 0; i < params.size(); i++)
		std::cout << "Param " << i << ": [" << params[i] << "]" << std::endl;
}


void	parseBuffer(std::string buffer)
{
	size_t pos;

	pos = buffer.find("\r\n");
	while (pos != std::string::npos)
	{
		std::string command = buffer.substr(0, pos);
		Message msg = tokenize(command);
		show_content(msg);
		buffer.erase(0, pos + 2);
		pos = buffer.find("\r\n");
	}
}

Message	tokenize(std::string raw)
{
	Message mess;
	size_t pos;
	std::vector<std::string> tmp;

	if (raw[0] == ':')
	{
		pos = raw.find(' ');
		if (pos != std::string::npos)
		{
			mess.setPrefix(raw.substr(0, pos));
			raw.erase(0, pos + 1);
		}
	}
	pos = raw.find(' ');
	if (pos != std::string::npos)
	{
		mess.setCommand(raw.substr(0, pos));
		raw.erase(0, pos + 1);
	}
	else
	{
		mess.setCommand(raw);
		return (mess);
	}
	while (!raw.empty())
	{
		while(raw[0] == ' ')
			raw.erase(0, 1);
		if (raw[0] == ':')
		{
			tmp.push_back(raw.substr(1, raw.length()));
			break ;
		}
		pos = raw.find(' ');
		if (pos != std::string::npos)
		{
			tmp.push_back(raw.substr(0, pos));
			raw.erase(0, pos + 1);
		}
		else
		{
			tmp.push_back(raw);
			raw.clear();
		}
	}
	mess.setParams(tmp);
	return (mess);
}
