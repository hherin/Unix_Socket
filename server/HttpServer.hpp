/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:21:22 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/28 15:04:18 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <list>
#include <vector>
#include <sys/select.h>

#include "ServerSocket.hpp"
#include "ClientSocket.hpp"
#include "../includes/webserv.hpp"
#include "../parser/ServerInfo.hpp"

class ServerSocket;
class ClientSocket;

class HttpServer
{
	private:

		std::list<ServerSocket>	_serverSocks;
		std::list<ClientSocket>	_clientSocks;
		fd_set					_readFds;
		// fd_set				_writeFds;
		int						_nbReadyFds;

	public:

		HttpServer();
		HttpServer(const HttpServer& copy);
		~HttpServer();

		HttpServer& operator=(HttpServer assign);

		// Create the socket and add socket id + socket fd
		void addServerSocket(ServerSocket sock);
		
		// Store the client fd when a connection is etablished
		void addClientSocket(int fdNewClient, int port, std::map<int, std::vector<ServerInfo> >& mSrv);
		
		// Infinite loop, sets fd_set with all fds for passive accept sockets + connected clients
		void etablishConnection(std::map<int, std::vector<ServerInfo> >& mSrv);

	private:

		// Set readfd with the content of a socket's list
		template <typename T>
		void addSocketsToFdSet(std::list<T>& sockets)
		{
			for (typename std::list<T>::iterator it = sockets.begin(); it != sockets.end(); ++it)
				FD_SET(it->getFd(), &_readFds);
		}

		// Check all passive accept socket and if one is ready, create a new client connection
		void connectNewClients(std::map<int, std::vector<ServerInfo> >& mSrv);

		// Checks all clients connections, and if one is communicating receive his request
		void requestHandler();

		friend void swap(HttpServer& a, HttpServer& b);

}; // class HttpServer

#endif