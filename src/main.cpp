/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 13:40:05 by jleray            #+#    #+#             */
/*   Updated: 2026/11/18 15:26:24 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>
#include "../includes/Header.hpp"

int	main(int ac, char **av)
{
	std::string test_buffer = "NICK jb\r\nUSER jb 0 * :Jean-Baptiste Leray\r\n";
	int port;
	std::string password;

	if (ac != 3)
	{
		std::cout << "please follow the following template :";
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}
	port = std::atoi(av[1]);
	if (port < 1024 || port > 65535)
	{
		std::cout << "The choosed port is out of range : " << port << std::endl;
		std::cout << "Please select a port between 1024 an 65535" << std::endl;
		return (1);
	}
	password = av[2];
	return (0);
}
