/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:14:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/21 16:24:50 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpServer.hpp"

HttpServer::HttpServer() {}

HttpServer::~HttpServer() {}

void HttpServer::addAcceptSocket(Socket sock)
{
	// Creating the socket and binding it to a port
	sock.createSocket();
	_acceptSocketsObjs.push_back(sock);
	
	// Saving socket fd
	_acceptSocketsFds.push_back(sock.getAcceptSocketFd());
}

void HttpServer::addClient(int fd)
{
	_clientsFds.push_back(fd);
}

void HttpServer::etablishConnection()
{
	while (true)
	{
		// Setting readFd with all passive accept sockets and all clients previously connected
		FD_ZERO(&_readFds);
		addSocketsToFdSet(_acceptSocketsFds);
		addSocketsToFdSet(_clientsFds);

		std::cout << "avant select\n";
		
		if ((_nbReadyFds = select(FD_SETSIZE, &_readFds, NULL, NULL, NULL)) < 0)
			throw "Error on select function\n";

		std::cout << "select ok\n";

		// If a passive socket was activated, creates a new client connection
		connectNewClients();
		requestHandler();
	}
}

void HttpServer::requestHandler()
{
	for (std::list<int>::iterator it = _clientsFds.begin(); it != _clientsFds.end(); ++it)
	{
		if (FD_ISSET(*it, &_readFds))
		{
			std::cout << "request handler\n";
			char buffer[2];
			bzero(buffer, 2);
			int n = recv(*it, buffer, 1, 0);

			if (n < 0)
				throw "Error on recv function\n";
				
			// Closing the connection
			else if (!n)
			{
				std::list<int>::iterator tmp = ++it;
				close(*tmp);
				_clientsFds.erase(tmp);
				
				continue ;
			}

			std::cout << "message is: " << static_cast<int>(buffer[0]) << "\n\n";
		}
	}
}

void HttpServer::addSocketsToFdSet(std::list<int>& sockets)
{
	for (std::list<int>::iterator it = sockets.begin(); it != sockets.end(); ++it)
		FD_SET(*it, &_readFds);
}

void HttpServer::connectNewClients()
{
	for (std::list<int>::iterator it = _acceptSocketsFds.begin(); it != _acceptSocketsFds.end(); ++it)
	{
		if (FD_ISSET(*it, &_readFds))
		{
			std::cout << "connect new clients\n";
			
			struct sockaddr_in addrCli;
			int lenCli = sizeof(addrCli);
			bzero((char *) &addrCli, sizeof(addrCli));

			// Creates a new socket for a client connection
			int newClient;
			if ((newClient = accept(*it, (struct sockaddr *)&addrCli, (socklen_t *)&lenCli)) < 0)
				throw "Error while trying to accept a new connection\n";
			
			_clientsFds.push_back(newClient);
			std::cout << "client succesfully added on fd " << newClient << "\n";

			// Case no other sockets waiting
			if (!--_nbReadyFds)
				break;
		}
	}
}