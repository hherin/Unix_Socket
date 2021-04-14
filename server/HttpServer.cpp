/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:14:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/14 17:30:31 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpServer.hpp"

HttpServer::HttpServer() {}

HttpServer::~HttpServer() {}

void HttpServer::addAcceptSocket(Socket sock)
{
	_acceptSocketsObjs.push_back(sock);
	_acceptSocketsObjs.back().createSocket();
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
		FD_ZERO(&_readFds);
		addSocketsToFdSet(_acceptSocketsFds);
		addSocketsToFdSet(_clientsFds);

		if ((_nbReadyFds = select(FD_SETSIZE, &_readFds, NULL, NULL, NULL)) < 0)
			throw "Error on select function";

		connectNewClients();

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
			struct sockaddr_in addrCli;
			int lenCli = sizeof(addrCli);
			bzero((char *) &addrCli, sizeof(addrCli));

			int newClient;
			if ((newClient = accept(*it, (struct sockaddr *)&addrCli, (socklen_t *)&lenCli)) < 0)
				throw "Error while trying to accept a new connection\n";
			
			_clientsFds.push_back(newClient);

			// Case no other sockets waiting
			if (!--_nbReadyFds)
				break;
		}
	}
}