#include "../../includes/Commands.hpp"
#include "NetworkData.hpp"

// Should we include the remaining err_codes? https://modern.ircdocs.horse/#pass-message and possiblity to cange serv Passwrd
void	Commands::Pass(Client& client, const std::string& passwrd) {
	if (NetworkData::getInstance()->getPassword() == passwrd)
	{
		client.setStatePasswrd(true);
		ft_send(client.getFd(), WELCOME);
		return;
	}
	client.setStatePasswrd(false);
	ft_send(client.getFd(), ERR_PASSWDMISMATCH(client));
}
