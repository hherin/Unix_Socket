/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:14:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/07 13:22:45 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpServer.hpp"


/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

HttpServer::HttpServer() :
	_readFds(), _writeFds(), _nbReadyFds() {}

HttpServer::~HttpServer() {}

HttpServer::HttpServer(const HttpServer& c) :
	_serverSocks(c._serverSocks), _clientSocks(c._clientSocks),
	_readFds(c._readFds), _writeFds(c._writeFds), _nbReadyFds(c._nbReadyFds) {}

HttpServer& HttpServer::operator=(HttpServer a)
{
	swap(a, *this);
	return *this;
}


/* ------------------------------------------------------------- */
/* --------------------------- METHODS ------------------------- */

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
		// Setting readFd with all passive accept sockets and all clients previously connected
		FD_ZERO(&_readFds);
		FD_ZERO(&_writeFds);
		
		addSocketsToReadFdSet<ServerSocket>(_serverSocks);
		addSocketsToReadFdSet<ClientSocket>(_clientSocks);
		addSocketsToWriteFdSet<ClientSocket>(_clientSocks);

		// Waiting for incoming connections on server sockets / client sockets
		if ((_nbReadyFds = select(FD_SETSIZE, &_readFds, &_writeFds, NULL, NULL)) < 0)
			throw std::runtime_error("Fatal error: select function failed\n");

		// If a passive socket was activated, creates a new client connection
		sendToClients();
		connectNewClients(mSrv);
		requestHandler();
	}
}


/* ------------------------------------------------------------- */
/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */

void HttpServer::sendToClients()
{
	for (std::list<ClientSocket>::iterator it = _clientSocks.begin(); it != _clientSocks.end(); ++it)
	{
		if (FD_ISSET(it->getFd(), &_writeFds))
		{
			send(it->getFd(), static_cast<void*>(it->getResponse().getBuffer().c_str()), 
					it->getResponse().getBuffer().size(), 0);
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
				throw std::runtime_error("Fatal error: recv function failed\n"); // A peaufiner, il ne faut surement pas compleement exit des qu'une fonction bug
				
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
		if (FD_ISSET(it->getFd(), &_readFds))
		{
			// Not use but need to be set for accept function
			struct sockaddr_in addrCli;
			int lenCli = sizeof(addrCli);
			bzero((char *) &addrCli, sizeof(addrCli));

			// Creates a new socket for a client connection
			int newClient;
			if ((newClient = accept(it->getFd(), (struct sockaddr *)&addrCli, (socklen_t *)&lenCli)) < 0)
				throw std::runtime_error("Fatal error: accept function failed\n");  // A peaufiner, il ne faut surement pas compleement exit des qu'une fonction bug
			
			// Setting the fd in non-blocking mode, then saving it
			fcntl(newClient, F_SETFL, O_NONBLOCK);
			addClientSocket(newClient, it->getPort(), mSrv);
			std::cout << "client succesfully added on fd " << newClient << "\n";

			// Case no other sockets waiting
			if (!--_nbReadyFds)
				break;
		}	
	}
}


/* ------------------------------------------------------------- */
/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

void swap(HttpServer& a, HttpServer& b)
{
	std::swap(a._serverSocks, b._serverSocks);
	std::swap(a._clientSocks, b._clientSocks);
	std::swap(a._readFds, b._readFds);
	std::swap(a._writeFds, b._writeFds);
	std::swap(a._nbReadyFds, b._nbReadyFds);
}