#include "Commands.hpp"

void	ft_send(const int& fd, const std::string& msg)
{
	send(fd, msg.c_str(), msg.length(), MSG_DONTWAIT);
}
