/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:04:02 by llefranc          #+#    #+#             */
/*   Updated: 2021/06/17 15:41:30 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

ClientSocket::ClientSocket(int fd, const std::vector<ServerInfo>* infoVirServs) :
		_fd(fd), _infoVirServs(infoVirServs), _request(infoVirServs) {}

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

int ClientSocket::getFd() const								{ return _fd; }

Request* ClientSocket::getRequest()							{ return &_request; }

Response* ClientSocket::getResponse()	            { return &_response; }


/* ------------------------------------------------------------- */
/* --------------------------- METHODS ------------------------- */

int ClientSocket::receiveRequest(const char* buffer)
{
	try
	{
		std::cerr << "BUFFER is: |" << buffer << "\n";

		_request += buffer;
		_request.parsingCheck();
	}

	// Setting the response with the StatusLine previously sent, and with this request
	// object containing the full request
	catch (const StatusLine& staLine)
	{
		printLog(" >> FD " + convertNbToString(getFd()) + ": Request received\n",
				_request.getBuffer());

        // Constructing response
        _response.setRequest(&_request);
        _response.setStatusLine(staLine);
        _response.setInfoVirtualServs(_infoVirServs);
		_response.fillBuffer();
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
