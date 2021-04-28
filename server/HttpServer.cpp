/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:14:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/28 15:20:17 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpServer.hpp"

HttpServer::HttpServer() 
	: _serverSocks(), _clientSocks(), _readFds(), _nbReadyFds() {}

HttpServer::~HttpServer() {}

HttpServer::HttpServer(const HttpServer& copy) :
	_serverSocks(copy._serverSocks), _clientSocks(copy._clientSocks),
	_readFds(copy._readFds), _nbReadyFds(copy._nbReadyFds) {}

HttpServer& HttpServer::operator=(HttpServer assign)
{
	swap(assign, *this);
	return *this;
}

void HttpServer::addServerSocket(ServerSocket sock)
{
	// Creating the socket and binding it to a port
	sock.createSocket();
	_serverSocks.push_back(sock);
}

void HttpServer::addClientSocket(int fdNewClient, int port, std::map<int, std::vector<ServerInfo> >& mSrv)
{
	_clientSocks.push_back(ClientSocket(fdNewClient, mSrv.find(port)->second));
}

void HttpServer::etablishConnection(std::map<int, std::vector<ServerInfo> >& mSrv)
{
	while (true)
	{
		try
		{
			// Setting readFd with all passive accept sockets and all clients previously connected
			FD_ZERO(&_readFds);
			addSocketsToFdSet<ServerSocket>(_serverSocks);
			addSocketsToFdSet<ClientSocket>(_clientSocks);

			// Waiting for incoming connections on server sockets / client sockets
			if ((_nbReadyFds = select(FD_SETSIZE, &_readFds, NULL, NULL, NULL)) < 0)
				throw "Error on select function\n";

			// If a passive socket was activated, creates a new client connection
			connectNewClients(mSrv);
			requestHandler();
		}
		catch (const char* error)
		{
			std::cerr << error;
		}
	}
}

void HttpServer::requestHandler()
{
	for (std::list<ClientSocket>::iterator it = _clientSocks.begin(); it != _clientSocks.end(); ++it)
	{
		if (FD_ISSET(it->getFd(), &_readFds))
		{
			char buffer[BUFFER_SIZE_REQUEST + 1]; // CHANGER ICI LA TAILLE DU BUFFER
			bzero(buffer, BUFFER_SIZE_REQUEST + 1);
			int n = recv(it->getFd(), buffer, BUFFER_SIZE_REQUEST, 0);

			if (n < 0)
				throw "Error on recv function\n";
				
			// Closing the connection (in ClientSocket destructor)
			else if (!n)
			{
				std::list<ClientSocket>::iterator tmp = ++it;
				_clientSocks.erase(tmp);
				continue ;
			}

			// Concatenate buffer to actual stored request
			it->receiveRequest(buffer);

			// Case no other sockets waiting
			if (!--_nbReadyFds)
				break;			
		}
	}
}

void HttpServer::connectNewClients(std::map<int, std::vector<ServerInfo> >& mSrv)
{
	for (std::list<ServerSocket>::iterator it = _serverSocks.begin(); it != _serverSocks.end(); ++it)
	{
		try
		{
			if (FD_ISSET(it->getFd(), &_readFds))
			{
			struct sockaddr_in addrCli;
			int lenCli = sizeof(addrCli);
			bzero((char *) &addrCli, sizeof(addrCli));

			// Creates a new socket for a client connection
			int newClient;
			if ((newClient = accept(it->getFd(), (struct sockaddr *)&addrCli, (socklen_t *)&lenCli)) < 0)
				throw "Error while trying to accept a new connection\n";
			
			addClientSocket(newClient, it->getPort(), mSrv);
			std::cout << "client succesfully added on fd " << newClient << "\n";

			// Case no other sockets waiting
			if (!--_nbReadyFds)
				break;
			}	
		}
		catch(const char* error)
		{
			std::cerr << error;	
		}
	}
}

//private

void swap(HttpServer& a, HttpServer& b)
{
	std::swap(a._serverSocks, b._serverSocks);
	std::swap(a._clientSocks, b._clientSocks);
	std::swap(a._readFds, b._readFds);
	std::swap(a._nbReadyFds, b._nbReadyFds);
}