/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldepenne <ldepenne@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 20:05:52 by ldepenne          #+#    #+#             */
/*   Updated: 2026/11/05 18:05:06 by ldepenne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Commands.hpp"
#include "../miniminiserv.hpp"

// Should we include the remaining err_codes? https://modern.ircdocs.horse/#pass-message and possiblity to cange serv Passwrd
void	Commands::Pass(Client& client, const std::string& passwrd) {
	if (serv::_pass == passwrd)
	{
		client.setStatePasswrd(true);
		ft_send(client.getFd(), GOODPASSWD);
		return;
	}
	client.setStatePasswrd(false);
	ft_send(client.getFd(), ERR_PASSWDMISMATCH(client));
}
