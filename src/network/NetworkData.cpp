#include "NetworkData.hpp"

NetworkData::NetworkData() {
}

NetworkData::NetworkData(int port, std::string password): _port(port), _password(password) {
	_listen_fd = -1;
	_epfd = -1;
	memset(&_ev, 0, sizeof(_ev));
}

NetworkData::NetworkData(const NetworkData& other) {
	_port = other._port;
	_password = other._password;
	_listen_fd = other._listen_fd;
	_epfd = other._epfd;
	_ev = other._ev;
}

NetworkData& NetworkData::operator=(const NetworkData& other) {
    if (this != &other) {
		_port = other._port;
		_password = other._password;
		_listen_fd = other._listen_fd;
		_epfd = other._epfd;
		_ev = other._ev;
    }
    return *this;
}

NetworkData::~NetworkData() {
	if (_epfd >= 0)
		close(_epfd);
	if (_listen_fd >= 0)
		close(_listen_fd);
}

void NetworkData::init() {
	this->setListenfd(setup_socket());
	bind_socket(*this);
	epoll_setup(*this);
}

const char* NetworkData::SocketFailed::what(void) const throw() {
	return ("socket() failed");
}

const char* NetworkData::SetsockoptFailed::what(void) const throw() {
	return ("setsockopt() failed");
}

const char* NetworkData::FcntlFailed::what(void) const throw() {
	return ("fcntl() failed");
}

const char* NetworkData::BindFailed::what(void) const throw() {
	return ("bind() failed");
}

const char* NetworkData::ListenFailed::what(void) const throw() {
	return ("listen() failed");
}

const char* NetworkData::EpollFailed::what(void) const throw() {
	return ("epoll() failed");
}

const char* NetworkData::EpollCTLFailed::what(void) const throw() {
	return ("epoll_ctl: event EPOLL_CTL_ADD failed");
}

int NetworkData::getPort(void) {
	return(_port);
}

std::string NetworkData::getPassword(void) {
	return(_password);
}

int NetworkData::getListenfd(void) {
	return(_listen_fd);
}

int NetworkData::getEpollfd(void) {
	return(_epfd);
}

void NetworkData::setPort(int port) {
	_port = port;
}

void NetworkData::setPassword(std::string password) {
	_password = password;
}

void NetworkData::setListenfd(int listen_fd) {
	_listen_fd = listen_fd;
}

void NetworkData::setEpollfd(int epfd) {
	_epfd = epfd;
}