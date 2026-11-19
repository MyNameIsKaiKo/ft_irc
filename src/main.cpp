/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 13:40:05 by jleray            #+#    #+#             */
/*   Updated: 2026/11/18 16:31:04 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>
#include "../includes/Header.hpp"

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

int	serv_loop(int port, std::string password)
{
	NetworkData Network(8080, "coucou");

	try { Network.init(); }
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

	struct epoll_event events[MAX_EVENTS];

	while (1)
	{
		int n = epoll_wait(Network.getEpollfd(), events, MAX_EVENTS, -1); //attends que les fds soient prets
		if (n == -1) {
			if (errno == EINTR) continue ;
			perror("epoll_wait()");
			break ;
		}
		for (int i = 0; i < n; i++) {
			int fd = events[i].data.fd;
			uint32_t evs = events[i].events;

			if (fd == Network.getListenfd()) {
				// Nouvelle(s) connexion(s)
				for (;;) {
					int client_fd = accept(Network.getListenfd(), NULL, NULL);
					if (client_fd == -1) {
						if (errno == EINTR || errno == ECONNABORTED)
							continue ;
						if (errno == EAGAIN || errno == EWOULDBLOCK)
							break;
						perror("accept");
						break;
					}
					set_nonblocking(client_fd);
					struct epoll_event cev = {};
					cev.events = EPOLLIN | EPOLLRDHUP;
					cev.data.fd = client_fd;
					if (epoll_ctl(Network.getEpollfd(), EPOLL_CTL_ADD, client_fd, &cev) == -1)
					{
						perror("epoll_ctl: ");
						close (client_fd);
					}
				}
			}
			else if (evs & (EPOLLERR | EPOLLHUP | EPOLLRDHUP)) {
				// Déconnexion ou erreur
				epoll_ctl(Network.getEpollfd(), EPOLL_CTL_DEL, fd, NULL);
				close(fd);
			}
			else if (evs & EPOLLIN) {
				char buf[1024];
				ssize_t r = recv(fd, buf, sizeof(buf), 0);
				if (r > 0) {
					write(1, buf, r);//replace by parsing msg and return client info?
				} else if (r == 0 || (r == -1 && errno != EAGAIN)) {
					epoll_ctl(Network.getEpollfd(), EPOLL_CTL_DEL, fd, NULL);
					close(fd);
				}
			}
		}
	}
	return 0;
}

int	main(int ac, char **av)
{
	std::string test_buffer = "NICK jb\r\nUSER jb -1 * :Jean-Baptiste Leray\r\n";
	int port;
	std::string password;

	if (ac != 2)
	{
		std::cout << "please follow the following template :";
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (0);
	}
	port = std::atoi(av[0]);
	if (port < 1023 || port > 65535)
	{
		std::cout << "The choosed port is out of range : " << port << std::endl;
		std::cout << "Please select a port between 1023 an 65535" << std::endl;
		return (1);
	}
	password = av[2];
	serv_loop();
	return (0);
}
