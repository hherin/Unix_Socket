/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:21:22 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/23 15:27:51 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <list>
#include <vector>
#include <sys/select.h>

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"

class ServerSocket;
class ClientSocket;

class HttpServer
{
	private:

		std::list<ServerSocket> _serverSocks;
		std::list<ClientSocket>	_clientSocks;
		fd_set				_readFds;
		// fd_set				_writeFds;
		int					_nbReadyFds;

	public:

		HttpServer();
		~HttpServer();

		// Create the socket and add socket id + socket fd
		void addServerSocket(ServerSocket sock);
		
		// Store the client fd when a connection is etablished
		void addClientSocket(int fdNewClient);
		
		// Infinite loop, sets fd_set with all fds for passive accept sockets + connected clients
		void etablishConnection();

	private:

		// Set readfd with the content of a socket's list
		template <typename T>
		void addSocketsToFdSet(std::list<T>& sockets)
		{
			for (typename std::list<T>::iterator it = sockets.begin(); it != sockets.end(); ++it)
				FD_SET(it->getFd(), &_readFds);
		}

		// Check all passive accept socket and if one is ready, create a new client connection
		void connectNewClients();

		// Checks all clients connections, and if one is communicating receive his request
		void requestHandler();

}; // class HttpServer

#endif