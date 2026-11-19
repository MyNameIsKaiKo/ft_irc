#include "../Commands.hpp"
#include "../miniminiserv.hpp"

static bool	validChar(Client& client,const std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!(isalnum(str[i]) || str[i] == '[' || str[i] == ']'
			|| str[i] == '{' || str[i] == '}' || str[i] == '|' || str[i] == '\\'))
			{
				ft_send(client.getFd(), ERR_ERRONEUSNICKNAME(client));
				return false;
			}
	}
	return true;
}

static bool	availableNickname(Client& client, const std::string& nickname)
{
	std::map<int, Client>::const_iterator	it = serv::_clients.begin();
	for (; it != serv::_clients.end(); it++)
	{
		if (client.getFd() != it->second.getFd() && nickname == it->second.getNickname())
		{
			ft_send(client.getFd(), ERR_NICKNAMEINUSE(client));
			return false;
		}
	}
	return true;
}

void	Commands::Nick(Client& client, const std::string& nickname) {
	if (!client.getStatePasswrd())
	{
		ft_send(client.getFd(), ERR_NOTREGISTERED(client));
		return;
	}
	if (nickname.empty())
	{
		ft_send(client.getFd(), ERR_NONICKNAMEGIVEN);
		return;
	}
	if (!validChar(client, nickname) || !availableNickname(client, nickname))
		return;
	std::string	lastNickname = client.getNickname();
	client.setNickname(nickname);
	std::map<int, Client>::const_iterator	it = serv::_clients.begin();
	for (; it != serv::_clients.end(); it++)
		ft_send(it->second.getFd(), SETNICKNAME(client, lastNickname)); /* @warning I send everyone but only people in the same channel should receive it*/

	if (client.getUsername().empty())
	{
		client.setUsername(nickname);
		client.setRealname(nickname);
		ft_send(client.getFd(), DEFAULTREALUSERNAME);
	}
}
