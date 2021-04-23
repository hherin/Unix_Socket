/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:14:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/22 15:51:34 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpServer.hpp"

HttpServer::HttpServer() {}

HttpServer::~HttpServer() {}

void HttpServer::addAcceptSocket(ServerSocket sock)
{
	// Creating the socket and binding it to a port
	sock.createSocket();
	_serverSocks.push_back(sock);
}

void HttpServer::addClient(int fdNewClient)
{
	_clientSocks.push_back(ClientSocket(fdNewClient));
}

void HttpServer::etablishConnection()
{
	while (true)
	{
		// Setting readFd with all passive accept sockets and all clients previously connected
		FD_ZERO(&_readFds);
		addSocketsToFdSet<ServerSocket>(_serverSocks);
		addSocketsToFdSet<ClientSocket>(_clientSocks);

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
	for (std::list<ClientSocket>::iterator it = _clientSocks.begin(); it != _clientSocks.end(); ++it)
	{
		if (FD_ISSET(it->getFd(), &_readFds))
		{
			std::cout << "request handler\n";
			char buffer[2];
			bzero(buffer, 2);
			int n = recv(it->getFd(), buffer, 1, 0);

			if (n < 0)
				throw "Error on recv function\n";
				
			// Closing the connection
			else if (!n)
			{
				std::list<ClientSocket>::iterator tmp = ++it;
				close(tmp->getFd());
				_clientSocks.erase(tmp);
				
				continue ;
			}

			// reprendre ici
			std::cout << "message is: " << static_cast<int>(buffer[0]) << "\n\n";
		}
	}
}

void HttpServer::connectNewClients()
{
	for (std::list<ServerSocket>::iterator it = _serverSocks.begin(); it != _serverSocks.end(); ++it)
	{
		if (FD_ISSET(it->getFd(), &_readFds))
		{
			std::cout << "connect new clients\n";
			
			struct sockaddr_in addrCli;
			int lenCli = sizeof(addrCli);
			bzero((char *) &addrCli, sizeof(addrCli));

			// Creates a new socket for a client connection
			int newClient;
			if ((newClient = accept(it->getFd(), (struct sockaddr *)&addrCli, (socklen_t *)&lenCli)) < 0)
				throw "Error while trying to accept a new connection\n";
			
			addClient(newClient);
			std::cout << "client succesfully added on fd " << newClient << "\n";

			// Case no other sockets waiting
			if (!--_nbReadyFds)
				break;
		}
	}
}