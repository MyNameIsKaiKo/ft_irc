#pragma once

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <cstdio>
#include <map>
#include "Channel.hpp"

#define MAX_EVENTS 32

class NetworkData
{
	private:
		int								_port;
		std::string						_password;
		int								_listen_fd;
		int								_epfd;
		struct epoll_event				_ev;
		static NetworkData				*_myself;
		std::map<int, Client>			_clients;
		std::map<std::string, Channel>	_channels;
		NetworkData();
		~NetworkData();
	public:
		class SocketFailed: public std::exception {public: const char* what() const throw();};
		class SetsockoptFailed: public std::exception {public: const char* what() const throw();};
		class FcntlFailed: public std::exception {public: const char* what() const throw();};
		class BindFailed: public std::exception {public: const char* what() const throw();};
		class ListenFailed: public std::exception {public: const char* what() const throw();};
		class EpollFailed: public std::exception {public: const char* what() const throw();};
		class EpollCTLFailed: public std::exception {public: const char* what() const throw();};

		static NetworkData* getInstance();
		void destroyInstance();

		void init();

		int getPort();
		std::string getPassword();
		int getListenfd();
		int getEpollfd();
		std::map<int, Client> getClients();
		std::map<std::string, Channel> getChannels();

		void addClient(const Client& client);
		void addChannel(Channel& channel);
		void setPort(const int port);
		void setPassword(const std::string password);
		void setListenfd(const int listen_fd);
		void setEpollfd(const int epfd);
};

//Init server functions
int		set_nonblocking(int fd);
int		setup_socket(void);
void	bind_socket(void);
void	epoll_setup(void);