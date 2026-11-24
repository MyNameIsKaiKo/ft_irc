#include "NetworkData.hpp"

NetworkData* NetworkData::_myself = NULL;

NetworkData::NetworkData(): _port(-1), _password("default"), _listen_fd(-1), _epfd(-1) {
	memset(&_ev, 0, sizeof(_ev));
}

NetworkData::~NetworkData() {
	if (_epfd >= 0)
		close(_epfd);
	if (_listen_fd >= 0)
		close(_listen_fd);
}

NetworkData* NetworkData::getInstance() {
	if (!_myself)
		_myself = new NetworkData;
	return (_myself);
}

void NetworkData::destroyInstance() {
	if (_myself)
		delete _myself;
}

void NetworkData::init() {
	setListenfd(setup_socket());
	bind_socket();
	epoll_setup();
}

const char* NetworkData::SocketFailed::what(void) const throw() { return ("socket() failed"); }
const char* NetworkData::SetsockoptFailed::what(void) const throw() { return ("setsockopt() failed"); }
const char* NetworkData::FcntlFailed::what(void) const throw() { return ("fcntl() failed"); }
const char* NetworkData::BindFailed::what(void) const throw() { return ("bind() failed"); }
const char* NetworkData::ListenFailed::what(void) const throw() { return ("listen() failed"); }
const char* NetworkData::EpollFailed::what(void) const throw() { return ("epoll() failed"); }
const char* NetworkData::EpollCTLFailed::what(void) const throw() { return ("epoll_ctl: event EPOLL_CTL_ADD failed"); }

int NetworkData::getPort(void) { return(_port); }
std::string NetworkData::getPassword(void) { return(_password); }
int NetworkData::getListenfd(void) { return(_listen_fd); }
int NetworkData::getEpollfd(void) { return(_epfd); }

void NetworkData::setPort(const int port) { _port = port; }
void NetworkData::setPassword(const std::string password) { _password = password; }
void NetworkData::setListenfd(const int listen_fd) { _listen_fd = listen_fd; }
void NetworkData::setEpollfd(const int epfd) { _epfd = epfd; }
 