#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "Client.hpp"

class Channel
{
	private:
		std::string 			_name;
		std::vector<Client&>	_members;
		std::vector<Client&>	_operators;
	public:
		Channel();
		Channel(std::string name, Client &operators);
		Channel(const Channel& other);
		Channel& operator=(const Channel& other);
		~Channel();
		void addMember(Client&);
		void addOperator(Client&);
		void removeMember(std::string name);
		void removeOperator(std::string name);
};
