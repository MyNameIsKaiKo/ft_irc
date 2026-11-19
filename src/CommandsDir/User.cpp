#include "../Commands.hpp"

/*
	parse: il faut ":" si le realname contient un espace
	parse: il faut "~" au debut du realname puisque le user se le def lui meme ?
	la commande doit etre ecrite: username 0 * realname
	on doit faire un define USERLEN=n pour def un taille max (~) s'il est la est inclu, il faut annoncer la longeure autorisé (param?)
	si ça depasse on decoupe sans rien dire le username
	la taille min est de 1 donc pas de vide mettre ERR_NEEDMOREPARAMS (461) trop court ou pas la
*/
void	Commands::User(Client &client, const std::string& username, const std::string& realname) // si username diff de nickname non non non
{
	if (!client.getStatePasswrd())
	{
		ft_send(client.getFd(), ERR_NOTREGISTERED(client));
		return;
	}
	if (client.getNickname() != "*" && client.getIsRegister())
	{
		ft_send(client.getFd(), ERR_ALREADYREGISTERED);
		return;
	}
	client.setUsername(username);
	client.setRealname(realname);
	ft_send(client.getFd(), SETREALUSERNAME(client));
	client.setIsRegister(true);
}
