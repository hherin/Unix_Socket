/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:55:48 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/14 15:26:55 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(int port, int maxClient) :
	_port(port), _maxClient(maxClient) {}

Socket::~Socket() {}
	
int Socket::getAcceptSocketFd() { return _acceptFd; }

void Socket::createSocket()
{
	// Creating a TCP socket
	if ((_acceptFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw "Error initialization socket\n";

	// Setting its options
	int yes = true;
	if (setsockopt(_acceptFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		throw "Error setting socket option\n";
	
	// Initializing structure for socket information (IP, port..)
	struct sockaddr_in socketAddr;
	bzero((char *) &socketAddr, sizeof(socketAddr));
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.s_addr = INADDR_ANY;
	socketAddr.sin_port = htons(_port);
	
	// Binding the socket to a port
	if (bind(_acceptFd, (struct sockaddr *) &socketAddr, sizeof(socketAddr)) < 0)
		throw "Error during bind function\n";

	listen(_acceptFd, _maxClient);
	std::cout << "http-socket() succesfully created on port " << _port << "\n";
}

