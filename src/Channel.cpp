#include "Channel.hpp"

Channel::Channel() {
}

Channel::Channel(const std::string name, Client &operators): _name(name) {
	_operators.insert(std::make_pair(operators.getFd(), operators));
}

Channel::~Channel() {
}

void Channel::addMember(const Client& member) {
	_members.insert(std::make_pair(member.getFd(), member));
}

void Channel::addOperator(const Client& operators) {
	_operators.insert(std::make_pair(operators.getFd(), operators));
}

/* @todo add msg if fd not found
	@warning add security */
void Channel::removeMember(const int fd) {
	std::map<int, Client>::iterator it = _members.find(fd);
	_members.erase(it);
}

/* @todo add msg if fd not found
	@warning add security */
void Channel::removeOperator(const int fd) {
	std::map<int, Client>::iterator it = _operators.find(fd);
	_operators.erase(it);
}

const std::string Channel::getName(void) { return _name; }

//for debug, remove later
void	Channel::printop(void) {
	std::cout << "members size: [" << _members.size() << "]" << std::endl;
	std::cout << "actif members in Channel [" << getName() << "]" << std::endl; 
	std::map<int, Client>::iterator it = _members.begin();
	for (; it != _members.end(); it++)
		std::cout << it->second.getNickname() << std::endl;
	std::cout << std::endl;
	std::cout << "actif operators in Channel [" << getName() << "]" << std::endl; 
	it = _operators.begin();
	for (; it != _operators.end(); it++)
		std::cout << it->second.getNickname() << std::endl;
}

/*	
	@todo join
	@todo send message to all users
	@todo research for channel size (defini par nous ou taille standard?)
	@todo set some reply message for clients
*/