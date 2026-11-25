#include "../../includes/Commands.hpp"

// Should we include the remaining err_codes? https://modern.ircdocs.horse/#pass-message and possiblity to cange serv Passwrd
void	Commands::Pass(Client& client, const std::string& passwrd, const std::string& servPasswrd) {
	if (servPasswrd == passwrd)
	{
		client.setStatePasswrd(true);
		ft_send(client.getFd(), GOODPASSWD);
		return;
	}
	client.setStatePasswrd(false);
	ft_send(client.getFd(), ERR_PASSWDMISMATCH(client));
}
