/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:04:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/06 12:18:22 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

ClientSocket::ClientSocket(int fd, const std::vector<ServerInfo>& infoVirServs) :
		_fd(fd), _infoVirServs(infoVirServs) {}

ClientSocket::~ClientSocket() {}

ClientSocket::ClientSocket(const ClientSocket& c) :
		_fd(c._fd), _infoVirServs(c._infoVirServs), 
		_request(c._request), _response(c._response) {}

ClientSocket& ClientSocket::operator=(ClientSocket a)
{
	swap(a, *this);
	return *this;
}


/* ------------------------------------------------------------- */
/* -------------------------- GETTERS -------------------------- */

int ClientSocket::getFd() const { return _fd; }

const Request& ClientSocket::getRequest() const { return _request; }

const Response& ClientSocket::getResponse() const { return _response; }


/* ------------------------------------------------------------- */
/* --------------------------- METHODS ------------------------- */

int ClientSocket::receiveRequest(const char* buffer)
{
	if (!_response.getCode())
	{
		try
		{
			_request += buffer;
			_request.parsingCheck();
		}
		catch (const StatusLine& staLine)
		{
			std::cerr << staLine << "\n";
			
			_response.setStatusLine(staLine);
			_response.setRequest(_request);
		}
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
	std::swap(a._response, b._response);
}
