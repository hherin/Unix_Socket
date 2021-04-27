/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:55:48 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/14 15:26:55 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int port, int maxClient) :
	_port(port), _maxClient(maxClient), _fd() {}

ServerSocket::~ServerSocket() {}
	
ServerSocket::ServerSocket(const ServerSocket& copy) :
		_fd(copy._fd) {}

ServerSocket& ServerSocket::operator=(ServerSocket assign)
{
	swap(assign, *this);
	return *this;
}
	
int ServerSocket::getFd() const { return _fd; }

int ServerSocket::getPort() const { return _port; }

void ServerSocket::createSocket()
{
	// Creating a TCP socket
	if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw "Error initialization socket\n";

	// Setting its options
	int yes = true;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		throw "Error setting socket option\n";
	
	// Initializing structure for socket information (IP, port..)
	struct sockaddr_in socketAddr;
	bzero((char *) &socketAddr, sizeof(socketAddr));
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.s_addr = INADDR_ANY;
	socketAddr.sin_port = htons(_port);
	
	// Binding the socket to a port
	if (bind(_fd, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) < 0)
		throw "Error during bind function\n";

	listen(_fd, _maxClient);
	std::cout << "http-socket() succesfully created on port " << _port << "\n";
}

//private

void swap(ServerSocket& a, ServerSocket& b)
{
	std::swap(a._fd, b._fd);
}