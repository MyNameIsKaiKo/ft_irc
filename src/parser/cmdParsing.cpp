#include "Commands.hpp"

void testFunc(Client &client)
{
	std::cout << "_cmd: " << client.getCmd() << std::endl;
}

void	parseCmd(Client &client)
{
	int			i = 0;

	const int	sizeTab = 3;
	std::string	cmdTab[sizeTab] = {"PASS", "NICK", "USER"};

	std::string	lineCmd = client.getCmd();
	std::string	cmd = lineCmd.substr(0, lineCmd.find_first_of(' '));
	size_t		endCmd = lineCmd.find_first_of("\r\n") - (lineCmd.find_first_of(' ') + 1);
	std::string	arg = lineCmd.substr(lineCmd.find_first_of(' ') + 1, endCmd);

	for (; i < sizeTab && cmd != cmdTab[i]; i++)
		;
	switch (i) {
		case 0:
			Commands::Pass(client, arg);
			break;
		case 1:
			Commands::Nick(client, arg);
			break;
		case 2:
		{
			std::string username = arg.substr(0, arg.find_first_of(' '));
			std::string realname = arg.substr(arg.find_first_of(' ') + 1, arg.find_first_of("\r\n"));
			Commands::User(client, username, realname);
		}
		default:
			std::cout << "please enter a command" << std::endl;
	}
	client.setCmd(lineCmd.substr(lineCmd.find_first_of("\r\n") + 2));
}
