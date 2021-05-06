/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:02:08 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/06 11:29:04 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <iostream>
#include <string>
#include <exception>

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

		int						_fd;
		std::vector<ServerInfo> _infoVirServs;
		
		Request					_request;
		Response				_response;

	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		// Initialize variables
		ClientSocket(int fd, const std::vector<ServerInfo>& infoVirServs);
		ClientSocket(const ClientSocket& c);
		~ClientSocket();
		ClientSocket& operator=(ClientSocket a);


		/* ------------------------------------------------------------- */
		/* -------------------------- GETTERS -------------------------- */

		// Return socket id
		int getFd() const;

		// Return request
		const Request& getRequest() const;

		// Return response
		const Response& getResponse() const;
	
	
		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

		// Add buffer into request, and request will parse the new line delimited by CRLF
		int receiveRequest(const char* buffer);
	
	private:

		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

		friend void swap(ClientSocket& a, ClientSocket& b);
		
}; // class ClientSocket

#endif