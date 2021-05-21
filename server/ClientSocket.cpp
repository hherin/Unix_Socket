/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:04:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/21 15:46:57 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

ClientSocket::ClientSocket(int fd, const std::vector<ServerInfo>* infoVirServs) :
		_fd(fd), _infoVirServs(infoVirServs) {}

ClientSocket::~ClientSocket() {}

ClientSocket::ClientSocket(const ClientSocket& c) :
		_fd(c._fd), _infoVirServs(c._infoVirServs), 
		_request(c._request), _respQueue(c._respQueue) {}

ClientSocket& ClientSocket::operator=(ClientSocket a)
{
	swap(a, *this);
	return *this;
}


/* ------------------------------------------------------------- */
/* -------------------------- GETTERS -------------------------- */

int ClientSocket::getFd() const								{ return _fd; }

Request* ClientSocket::getRequest()							{ return &_request; }

std::queue<Response>* ClientSocket::getResponsesQueued()	{ return &_respQueue; }


/* ------------------------------------------------------------- */
/* --------------------------- METHODS ------------------------- */

int ClientSocket::receiveRequest(const char* buffer)
{
	try
	{
		_request += buffer;
		_request.parsingCheck();
	}

	// Setting the response with the StatusLine previously sent, and with this request
	// object containing the full request
	catch (const StatusLine& staLine)
	{
		_respQueue.push(Response(&_request, staLine, _infoVirServs));
		_respQueue.back().fillBuffer();
		
		// Response was created, clearing request object for next incoming request
		_request.clear();
	}
	
	return 0;
}


/* ------------------------------------------------------------- */
/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

void swap(ClientSocket& a, ClientSocket& b)
{
	std::swap(a._fd, b._fd);
	std::swap(a._infoVirServs, b._infoVirServs);
	std::swap(a._request, b._request);
	std::swap(a._respQueue, b._respQueue);
}
