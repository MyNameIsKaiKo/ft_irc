/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nredouan <nredouan@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 19:58:42 by ldepenne          #+#    #+#             */
/*   Updated: 2026/11/24 13:24:46 by nredouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <iostream>
# include "Client.hpp"
# include <sys/socket.h>
# include <cstring>

# define SERVNAME std::string("localhost")

class Commands
{
	public:
		static void	Pass(NetworkData &Network, Client &client, const std::string& passwrd);
		static void	Nick(Client &client, const std::string& nickname);
		static void	User(Client &client, const std::string& username, const std::string& realname);
};

void	ft_send(const int& fd, const std::string& msg);

#endif
