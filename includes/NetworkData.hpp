#pragma once

#include <netinet/in.h>
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

#define MAX_EVENTS 32

class NetworkData
{
	private:
		int					_port;
		std::string			_password;
		int					_listen_fd;
		int					_epfd;
		struct epoll_event	_ev;
	public:
		NetworkData();
		NetworkData(int port, std::string password);
		NetworkData(const NetworkData& other);
		NetworkData& operator=(const NetworkData& other);
		~NetworkData();
		class SocketFailed: public std::exception {
			public: const char* what() const throw(); };
		class SetsockoptFailed: public std::exception {
			public: const char* what() const throw(); };
		class FcntlFailed: public std::exception {
			public: const char* what() const throw(); };
		class BindFailed: public std::exception {
			public: const char* what() const throw(); };
		class ListenFailed: public std::exception {
			public: const char* what() const throw(); };
		class EpollFailed: public std::exception {
			public: const char* what() const throw(); };
		class EpollCTLFailed: public std::exception {
			public: const char* what() const throw(); };
		void init();
		int getPort();
		std::string getPassword();
		int getListenfd();
		int getEpollfd();
		void setPort(int port);
		void setPassword(std::string password);
		void setListenfd(int listen_fd);
		void setEpollfd(int epfd);
};

//Init server functions
int		set_nonblocking(int fd);
int		setup_socket(void);
void	bind_socket(NetworkData &Network);
void	epoll_setup(NetworkData &Network);