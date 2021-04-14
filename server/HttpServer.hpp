/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:21:22 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/14 17:20:30 by llefranc         ###   ########.fr       */
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

		void addAcceptSocket(Socket sock);
		void addClient(int fd);
		void etablishConnection();

	private:

		void addSocketsToFdSet(std::list<int>& sockets);
		void connectNewClients();

}; // class HttpServer

#endif