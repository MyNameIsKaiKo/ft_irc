/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 13:40:05 by jleray            #+#    #+#             */
/*   Updated: 2026/11/25 08:47:28 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>
#include "../includes/Header.hpp"

int	serv_loop(int port, std::string password)
{
	NetworkData Network(port, password);

	try { Network.init(); }
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
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
				if (r > 0) 
				{
					std::string s = std::string(buf, r);
					parseBuffer(s);
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

	if (ac != 3)
	{
		std::cout << "please follow the following template :";
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (0);
	}
	port = std::atoi(av[1]);
	if (port < 1023 || port > 65535)
	{
		std::cout << "The choosed port is out of range : " << port << std::endl;
		std::cout << "Please select a port between 1023 an 65535" << std::endl;
		return (1);
	}
	password = av[2];
	if (serv_loop(port, password))
		return (1);
	return (0);
}
