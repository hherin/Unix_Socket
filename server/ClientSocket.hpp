/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:02:08 by llefranc          #+#    #+#             */
/*   Updated: 2021/06/08 16:34:38 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <iostream>
#include <string>
#include <exception>
#include <queue>

#include "Request.hpp"
#include "Response.hpp"
#include "msg_format/StatusLine.hpp"
#include "../includes/webserv.hpp"
#include "../parser/ServerInfo.hpp"

class ClientSocket
{
	private:

		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		int								_fd;			// File descriptor receiving / sending with the client
		std::vector<ServerInfo>*		_infoVirServs;	// Servers blocks from config file that match a specific port
		
		Request							_request;		// Object containing the request
		std::queue<Response>			_respQueue;		// Queue containing the responses created from request object

	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		ClientSocket(int fd, std::vector<ServerInfo>* infoVirServs);
		ClientSocket(const ClientSocket& c);
		~ClientSocket();
		ClientSocket& operator=(ClientSocket a);


		/* ------------------------------------------------------------- */
		/* -------------------------- GETTERS -------------------------- */

		// Return socket id
		int getFd() const;

		// Return request
		Request* getRequest();

		// Return responses queue
		std::queue<Response>* getResponsesQueued();
	
	
		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

		// Add buffer into request, and request will parse the new line delimited by CRLF
		int receiveRequest(const char* buffer);
	

		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

		friend void swap(ClientSocket& a, ClientSocket& b);
		
}; // class ClientSocket

#endif