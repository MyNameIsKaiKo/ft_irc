#include "../../includes/Commands.hpp"

void	dispatchCommand(Message& msg, Client& client, const std::string& servPassword, const std::map<int, Client>& clients)
{
	std::string					cmd = msg.getCommand();
	std::vector<std::string>	params = msg.getParams();

	if (cmd == "PASS")
	{
		if (params.empty())
		{
			ft_send(client.getFd(), ":" + SERVNAME + " 461 " + client.getNickname() + " PASS :Not enough parameters\r\n");
			return ;
		}
		Commands::Pass(client, params[0], servPassword);
	}
	else if (cmd == "NICK")
	{
		Commands::Nick(client, params.empty() ? "" : params[0], clients);
	}
	else if (cmd == "USER")
	{
		if (params.size() < 4)
		{
			ft_send(client.getFd(), ":" + SERVNAME + " 461 " + client.getNickname() + " USER :Not enough parameters\r\n");
			return ;
		}
		Commands::User(client, params[0], params[3]);
	}
}
