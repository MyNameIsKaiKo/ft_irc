/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 02:15:21 by jleray            #+#    #+#             */
/*   Updated: 2026/11/18 15:22:24 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>

class Message
{
	private:
		int	clientFd;
		std::string prefix;
		std::string command;
		std::vector<std::string> params;

	 public:
		Message();
		Message(const Message& other);
		Message&					operator=(const Message& other);
		void						setClientFd(const int cFd);
		void						setPrefix(const std::string pref);
		void						setCommand(const std::string com);
		void						setParams(const std::vector<std::string> params);
		int							getClientFd(void);
		std::string					getPrefix(void);
		std::string					getCommand(void);
		std::vector<std::string>	getParams(void);
		~Message();
};

#endif
