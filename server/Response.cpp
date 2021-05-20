/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:23:57 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/20 13:45:44 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"


/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

Response::Response() {}

Response::Response(const Request& req, const StatusLine& staLine, const std::vector<ServerInfo>& servInfo) :
	_servInfo(servInfo), _req(req), _staLine(staLine) {}

Response::Response(const Response& c) : 
	_servInfo(c._servInfo), _req(c._req), _staLine(c._staLine), _headers(c._headers), _body(c._body) {}

Response::~Response() {}

Response& Response::operator=(Response a)
{
	swap(a, *this);
	return *this;
}


/* ------------------------------------------------------------- */
/* --------------------------- SETTERS ------------------------- */

void Response::setRequest(const Request& req)
{
	_req = req;
}

void Response::setStatusLine(const StatusLine& staLine)
{
	_staLine = staLine;
}


/* ------------------------------------------------------------- */
/* --------------------------- GETTERS ------------------------- */

const StatusLine& Response::getStatusLine() const
{
	return _staLine;
}

int Response::getCode() const
{
	return _staLine.getCode();
}

const std::string& Response::getBuffer() const
{
	return _buffer;
}


/* ------------------------------------------------------------- */
/* --------------------------- METHODS ------------------------- */

void Response::clear()
{
	_req.clear();
	_staLine.clear();
	_headers.clear();
	_body.clear();
	_buffer.clear();
}

void Response::fillBuffer()
{
	_buffer = convertNbToString(_staLine.getCode()) + " " + _staLine.getReason();
	if (!_staLine.getAdditionalInfo().empty())
		_buffer += " (" + _staLine.getAdditionalInfo() + ")";
	_buffer += CLRF;

	// if (request.getMethod())
		// _buffer += execGET();
}


// HELENE FONCTION qui store la page a renvoyer dans le body de la reponse
void Response::execGET()
{

}

/* ------------------------------------------------------------- */
/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

void swap(Response& a, Response& b)
{
	std::swap(a._servInfo, b._servInfo);
	swap(a._req, b._req);
	swap(a._staLine, b._staLine);
	std::swap(a._headers, b._headers);
	std::swap(a._body, b._body);
}
