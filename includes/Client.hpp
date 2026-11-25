/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldepenne <ldepenne@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 20:13:17 by ldepenne          #+#    #+#             */
/*   Updated: 2026/11/25 09:02:28 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class	Client {
	public:
		Client(int fd);
		~Client();
		void	appendBuffer(const std::string& data);

		//getFunc
		int				getFd() const;
		std::string		getRealname() const;
		std::string		getUsername() const;
		std::string		getNickname() const;
		std::string		getCmd() const;
		std::string&	getBuffer();
		bool			getStatePasswrd() const;
		bool			getIsRegister() const;

		//setFunc
		void		setRealname(std::string newNick);
		void		setUsername(std::string newNick);
		void		setNickname(std::string newNick);
		void		setCmd(std::string cmd);
		void		setStatePasswrd(bool val);
		void		setIsRegister(bool val);

	private:
		int			_fd;
		std::string	_realname;
		std::string	_username;
		std::string	_nickname; //doit etre unique + voir regle
		std::string	_linecmd;
		std::string	_recvBuffer;
		bool		_password;
		bool		_isRegister;
};

#endif
