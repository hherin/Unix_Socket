/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:14:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/06/16 15:34:10 by hherin           ###   ########.fr       */
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
	_clientSocks.push_back(ClientSocket(fdNewClient, &(mSrv.find(port)->second)));
}

void HttpServer::etablishConnection(std::map<int, std::vector<ServerInfo> >& mSrv)
{
	struct timeval tv;

	while (true)
	{
		tv.tv_sec = MAX_SEC_TIMEOUT;
		tv.tv_usec = MAX_USEC_TIMEOUT;

		// Setting readFd with all passive accept sockets and all clients previously connected
		FD_ZERO(&_readFds);
		FD_ZERO(&_writeFds);
		
		addSocketsToReadFdSet<ServerSocket>(_serverSocks);
		addSocketsToReadFdSet<ClientSocket>(_clientSocks);
		addSocketsToWriteFdSet<ClientSocket>(_clientSocks);

		// Waiting for incoming connections on server sockets / client sockets
		if ((_nbReadyFds = select(FD_SETSIZE, &_readFds, &_writeFds, NULL, &tv)) < 0)
			throw std::runtime_error("Fatal error: select function failed\n");
		else if (!_nbReadyFds)
			throw std::runtime_error("Webserv timeout\n");

		// Send responses to clients
		sendToClients();
		// If a passive socket was activated, creates a new client connection
		connectNewClients(mSrv);
		// Receive from client
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
			int n = 0;
			Response *resp = &it->getResponsesQueued()->front();

			// Doesn't handle the case if send can't send everything in one time. Send the first response
			// of the queue
			if ((n = send(it->getFd(), static_cast<const void*>(resp->getBuffer().c_str()), 
					resp->getBuffer().size(), 0)) < 1)
				throw std::runtime_error("Fatal error: send function failed\n");
			
			printLog(" >> FD " + convertNbToString(it->getFd()) + ": Response sent (code: " +
                    convertNbToString(resp->getCode()) + ")\n", resp->getBuffer());
			
            // // If an error occured, closing the connection
            if (resp->getCode() >= 400)
            {
                printLog(" >> FD " + convertNbToString(it->getFd()) + ": Connection closed due to error "
                        + convertNbToString(resp->getCode()) + "\n");

                std::list<ClientSocket>::iterator tmp = it--;

                close(tmp->getFd());
                _clientSocks.erase(tmp);
            }
            
			// After sending the response without encoutering any error, removing it from the queue
            else
                it->getResponsesQueued()->pop();
		}
	}
}

void HttpServer::requestHandler()
{
	for (std::list<ClientSocket>::iterator it = _clientSocks.begin(); it != _clientSocks.end();)
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
				printLog(" >> FD " + convertNbToString(it->getFd()) + ": Connection closed\n");

				// Need to use a tmp iterator because otherwise it is invalidated after erase
				std::list<ClientSocket>::iterator tmp = it++;
				_clientSocks.erase(tmp);

				continue ;
			}

			// Concatenate buffer to actual stored request
			it->receiveRequest(buffer);
				
			// Case no other sockets waiting
			if (!--_nbReadyFds)
				break;
		}
		++it;
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
			printLog(" >> FD " + convertNbToString(newClient) + ": Client socket created\n");

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