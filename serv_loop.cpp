#include "NetworkData.hpp"

#include <stdio.h>

int	main(void)
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
		int n = epoll_wait(Network.getEpollfd(), events, MAX_EVENTS, -1);//attends que les fds soient prets
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

