/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:21:22 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/07 13:17:58 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <list>
#include <vector>
#include <sys/select.h>
#include <fcntl.h>

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "../includes/webserv.hpp"
#include "../parser/ServerInfo.hpp"

class ServerSocket;
class ClientSocket;

class HttpServer
{
	private:

		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		std::list<ServerSocket>	_serverSocks;
		std::list<ClientSocket>	_clientSocks;
		fd_set					_readFds;
		fd_set					_writeFds;
		int						_nbReadyFds;


	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */
		
		HttpServer();
		HttpServer(const HttpServer& c);
		~HttpServer();
		HttpServer& operator=(HttpServer a);


		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */
		
		// Create the socket and add socket id + socket fd
		void addServerSocket(ServerSocket sock);
		
		// Store the client fd when a connection is etablished
		void addClientSocket(int fdNewClient, int port, std::map<int, std::vector<ServerInfo> >& mSrv);
		
		// Infinite loop, sets fd_set with all fds for passive accept sockets + connected clients
		void etablishConnection(std::map<int, std::vector<ServerInfo> >& mSrv);


	private:

		/* ------------------------------------------------------------- */
		/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */
		
		// Set readfd with the content of a socket's list
		template <typename T>
		void addSocketsToReadFdSet(std::list<T>& sockets)
		{
			for (typename std::list<T>::iterator it = sockets.begin(); it != sockets.end(); ++it)
				FD_SET(it->getFd(), &_readFds);
		}

		// Set writefd with the content of a socket's list
		template <typename T>
		void addSocketsToWriteFdSet(std::list<T>& sockets)
		{
			for (typename std::list<T>::iterator it = sockets.begin(); it != sockets.end(); ++it)
				if (!(it->getResponse().getBuffer().empty()))
					FD_SET(it->getFd(), &_writeFds);
		}

		// Check all passive accept socket and if one is ready, create a new client connection
		void connectNewClients(std::map<int, std::vector<ServerInfo> >& mSrv);

		// Checks all clients connections, and if one is communicating receive his request
		void requestHandler();

		void sendToClients();


	public:
	
		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

		friend void swap(HttpServer& a, HttpServer& b);

}; // class HttpServer

#endif