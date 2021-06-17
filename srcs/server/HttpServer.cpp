/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:14:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/06/17 16:16:40 by llefranc         ###   ########.fr       */
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

            // const char *toSend = resp->getBuffer().c_str();
            // size_t sizeToSend;

            /* NEED TO FIX THIS */

			// Doesn't handle the case if send can't send everything in one time. Send the first response
			// of the queue

            // int fd = open("/Users/llefranc/Rendu/42cursus/Unix_Socket/www/tests/test_cgi/img/negroni.png", O_RDONLY);
            // char buffer[SEND_BUFFER_SIZE + 1] = {0};

            // size_t headersPos = resp->getBuffer().find("\r\n\r\n");

            // std::cout << "HEADERS:|" << resp->getBuffer().substr(0, headersPos + 4) << "|\n-------------\n";
            // send(it->getFd(), static_cast<const void*>(resp->getBuffer().c_str()), headersPos, 0);

            // do
			// {
            //     // (void)toSend;
            //     std::cerr << "hello\n";
            //     memset(buffer, 0, SEND_BUFFER_SIZE + 1);
            //     sizeToSend = read(fd, buffer, SEND_BUFFER_SIZE);
            //     std::cerr << "size read = " << sizeToSend << "\n";

            //     sizeToSend = (leftToSend > SEND_BUFFER_SIZE) ? SEND_BUFFER_SIZE : leftToSend;
            //     std::cerr << "hello3\n";
                
            //     n = write(it->getFd(),static_cast<const void*>(buffer), sizeToSend );
            //     // n = send(it->getFd(), static_cast<const void*>(it->getResponse()->getBuffer().c_str()),
            //     //          it->getResponse()->getBuffer().size(), 0);
            //     std::cerr << "hello4\n";

            //     leftToSend -= sizeToSend;
            //     std::cerr << "size to send: " << sizeToSend << " and send " << n << " octets, left to send: " << leftToSend << "\n";
                
            // } while (n != -1 && leftToSend);
			
			const std::string *buffer = &it->getResponse()->getBuffer();
            size_t leftToSend = buffer->size();
            size_t octetsSent = 0;

            do
			{
                n = send(it->getFd(), static_cast<const void*>(buffer->c_str() + octetsSent),
                        buffer->size(), 0);

                octetsSent += n;
                leftToSend -= n;
                
            } while (n != -1 && leftToSend);
            
			if (n != -1)
                printLog(" >> FD " + convertNbToString(it->getFd()) + ": Response sent (code: " +
                        // convertNbToString(resp->getCode()) + ")\n", resp->getBuffer());
                        convertNbToString(it->getResponse()->getCode()) + "), connection closed\n");
			else
            {
                printLog(" >> FD " + convertNbToString(it->getFd()) + 
                        ": Failed to send response, connection closed\n");
            }
            
            std::list<ClientSocket>::iterator tmp = it--;
            closeConnection(&tmp);

            // Case no other sockets waiting
			if (!--_nbReadyFds)
				break;
		}
	}
}

void HttpServer::requestHandler()
{
	for (std::list<ClientSocket>::iterator it = _clientSocks.begin(); it != _clientSocks.end(); ++it)
	{
		if (FD_ISSET(it->getFd(), &_readFds))
		{
			char buffer[REQUEST_BUFFER_SIZE + 1];
			bzero(buffer, REQUEST_BUFFER_SIZE + 1);
			int n = recv(it->getFd(), buffer, REQUEST_BUFFER_SIZE, 0);

			if (n < 0)
            {
                printLog(" >> FD " + convertNbToString(it->getFd()) + ": Error on recv function, connection closed\n");
                std::list<ClientSocket>::iterator tmp = it--;
                closeConnection(&tmp);
            }

			// Client closed the connection
			else if (!n)
			{
				printLog(" >> FD " + convertNbToString(it->getFd()) + ": recv function returned 0, connection closed\n");
                std::list<ClientSocket>::iterator tmp = it--;
                closeConnection(&tmp);
			}

			// Concatenate buffer to actual stored request
            else
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
			printLog(" >> FD " + convertNbToString(newClient) + ": Client socket created\n");

			// Case no other sockets waiting
			if (!--_nbReadyFds)
				break;
		}	
	}
}

void HttpServer::closeConnection(std::list<ClientSocket>::iterator *it)
{
    close((*it)->getFd());
    _clientSocks.erase(*it);
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