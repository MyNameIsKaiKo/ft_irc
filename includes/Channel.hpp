#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "Client.hpp"

class Channel
{
	private:
		std::string 			_name;
		std::map<int, Client>	_members;
		std::map<int, Client>	_operators;
	public:
		Channel();
		Channel(std::string name, Client &operators);
		~Channel();
		void addMember(const Client& members);
		void addOperator(const Client& oprators);
		void removeMember(const int fd);
		void removeOperator(const int fd);

		void printop(void);
};
