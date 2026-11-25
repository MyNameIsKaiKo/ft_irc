#include "NetworkData.hpp"

//Setup a fd to be nonblocking
int set_nonblocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
		return -1;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

//Setup of the socket for epoll()
int setup_socket(void)
{
	int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	int	on = 1;

	if (listen_fd < 0)
		throw NetworkData::SocketFailed();
	if (setsockopt(listen_fd, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on)) == -1)//sert a autoriser la reutilisation de l'adresse et du port du serv
		throw NetworkData::SetsockoptFailed();
	//SOL_SOCKET: l'option est generique à la socket, non spé a un protocole reseau en particulier
	//SO_REUSEADDR: Socket Reuse Address, indique au noyau qu'il peut reutiliser cette adresse et ce port
	if (set_nonblocking(listen_fd) == -1)
		throw NetworkData::FcntlFailed();
	return listen_fd;
}

//Bind the socket
void bind_socket(NetworkData &Network)
{
	sockaddr_in serverAddress;

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(Network.getPort());
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	if (bind(Network.getListenfd(), (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
		throw NetworkData::BindFailed();
}

//Set listen backlog and init epoll() struct
void epoll_setup(NetworkData &Network)
{
	struct epoll_event	ev;
	int					epfd;
	//set listen backlog
	if (listen(Network.getListenfd(), MAX_EVENTS) == -1)
		throw NetworkData::ListenFailed();
	//init epollfd struct
	epfd = epoll_create1(EPOLL_CLOEXEC);//creer l'instance epoll(), retourne le fd de l'instance
	if (epfd == -1)
		throw NetworkData::EpollFailed();
	Network.setEpollfd(epfd);
	ev.events = EPOLLIN;
	ev.data.fd = Network.getListenfd();
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, Network.getListenfd(), &ev) == -1)//ajoute, modifie ou retire un fd
		throw NetworkData::EpollCTLFailed();
}
