/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:21:22 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/21 16:12:03 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <list>
#include <vector>
#include <sys/select.h>

#include "Socket.hpp"

class HttpServer
{
	private:

		std::vector<Socket> _acceptSocketsObjs;
		std::list<int>		_acceptSocketsFds;
		std::list<int>		_clientsFds;
		fd_set				_readFds;
		// fd_set				_writeFds;
		int					_nbReadyFds;

	public:

		HttpServer();
		~HttpServer();

		// Create the socket and add socket id + socket fd
		void addAcceptSocket(Socket sock);
		
		// Store the client fd when a connection is etablished
		void addClient(int fd);
		
		// Infinite loop, sets fd_set with all fds for passive accept sockets + connected clients
		void etablishConnection();

	private:

		// Set readfd with the content of a socket's list
		void addSocketsToFdSet(std::list<int>& sockets);

		// Check all passive accept socket and if one is ready, create a new client connection
		void connectNewClients();

		// Checks all clients connections, and if one is communicating receive his request
		void requestHandler();

}; // class HttpServer

#endif