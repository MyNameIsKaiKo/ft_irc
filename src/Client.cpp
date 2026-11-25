/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldepenne <ldepenne@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 20:12:16 by ldepenne          #+#    #+#             */
/*   Updated: 2026/11/25 09:02:06 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd) : _fd(fd), _nickname("*"), _password(false), _isRegister(false) {}

Client::~Client() {}

void		Client::appendBuffer(const std::string& data) 
{this->_recvBuffer += data;}

//getFunc
int			Client::getFd() const { return _fd; }
std::string	Client::getRealname() const { return _realname; }
std::string	Client::getUsername() const { return _username; }
std::string	Client::getNickname() const { return _nickname; }
std::string	Client::getCmd() const { return _linecmd;}
bool		Client::getStatePasswrd() const { return _password; }
bool		Client::getIsRegister() const { return _isRegister; }
std::string&	Client::getBuffer() {return (this->_recvBuffer);}

//setFunc
void	Client::setRealname(std::string realname) { _realname = realname; }
void	Client::setUsername(std::string username) { _username = username; }
void	Client::setNickname(std::string nickname) { _nickname = nickname; }
void	Client::setCmd(std::string cmd) { _linecmd = cmd; }
void	Client::setStatePasswrd(bool val) { _password = val; }
void	Client::setIsRegister(bool val) { _isRegister = val; }
