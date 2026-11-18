/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:23:36 by jleray            #+#    #+#             */
/*   Updated: 2026/11/18 15:36:46 by jleray           ###   ########.fr       */
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
