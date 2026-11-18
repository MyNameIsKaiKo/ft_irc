/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:23:36 by jleray            #+#    #+#             */
/*   Updated: 2026/11/18 16:30:27 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Parser.hpp"

void	parseBuffer(std::string& buffer)
{
	size_t pos;

	pos = buffer.find("\r\n");
	while (pos != std::string::npos)
	{
		std::string command = buffer.substr(0, pos);
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
			mess.setParams(tmp);
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
	return (mess);
}
