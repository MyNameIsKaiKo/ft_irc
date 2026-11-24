#include "Channel.hpp"

Channel::Channel() {
}

Channel::Channel(const std::string name, Client &operators): _name(name) {
	_operators.push_back(operators);
}

Channel::Channel(const Channel& other) {
    *this = other;
}

Channel& Channel::operator=(const Channel& other) {
	if (this != &other) {
	}
	return *this;
}

Channel::~Channel() {
}

void Channel::addMember(Client& member) {
	_members.push_back(member);
}

void Channel::addOperator(Client& operators) {
	_operators.push_back(operators);
}

void Channel::removeMember(std::string name) {

}

void Channel::removeOperator(std::string name) {

}