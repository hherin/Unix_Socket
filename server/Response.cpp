/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:23:57 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/21 13:43:28 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"


/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

Response::Response() {}

Response::Response(Request* req, const StatusLine& staLine, const std::vector<ServerInfo>* servInfo) :
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

void Response::setRequest(Request* req)
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
	_staLine.clear();
	_headers.clear();
	_body.clear();
	_buffer.clear();
}

void Response::fillBuffer()
{
	if (_req.getMethod() ==  GET)
		execGET();

	setHeaders();
	
	// Storing status line in buffer
	_buffer = "HTTP/1.1 " + convertNbToString(_staLine.getCode()) + " " + _staLine.getReason();
	if (!_staLine.getAdditionalInfo().empty())
		_buffer += " (" + _staLine.getAdditionalInfo() + ")";
	_buffer += CLRF;

	// Storing headers in buffer
	for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); ++it)
			_buffer += it->first + ": " + it->second + CLRF;
}

void Response::setHeaders()
{
	setHeaderServer();
	setHeaderContentLenght();
	setHeaderDate();
}

// HELENE FONCTION qui store la page a renvoyer dans le body de la reponse
// void Response::execGET()
// {
// 	// std::vector<std::string> path = stringDelimSplit(_req.getPath(), "/");							// URI requested is splited 
	
// 	// for (size_t i = 0; i < _servInfo.size(); i++){													// loop for each 
// 	// 	std::vector<ServerInfo> loc = _servInfo[i].getLocation();
// 	// 	for (size_t j = 0; j < loc.size(); j++){
// 	// 		std::vector<std::string> locName = stringDelimSplit((loc[i].getNames())[0], "/");
// 	// 		if (locName[0].compare(0, path[0].size() + 1), path[0]){
				
// 	// 		}
// 	// 	}
// 	// 	if (_req.getHeaders().find("host"))
// 	// }
// 	// FileParser reqFile();
	
// }


/* ------------------------------------------------------------- */
/* ----------------------- PRIVATE METHODS --------------------- */

void Response::setHeaderContentLenght()
{
	_headers["Content-lenght"] = convertNbToString(_body.getSize());
}

void Response::setHeaderServer()
{
	_headers["Server"] = "webserv";
}

void Response::setHeaderDate()
{
	// current date and time on the current system
	time_t now = time(0);

	// convert now to string form
	char* date_time = ctime(&now);

	// Splitting date line and removing '\n'
	std::vector<std::string> date = splitWithSep(date_time, ' ');
	date.back().back() = '\0';

	// Formating header date.
	// ctime format = Thu May 20 14:33:40 2021 >> to header date format : Thu, 20 May 2021 12:16:42 GMT
	_headers["Date"] = date[0] + ", " + date[2] + " " + date[1] + " " + date[4] + " " + date[3] + " GMT";
}


/* ------------------------------------------------------------- */
/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

void swap(Response& a, Response& b)
{
	std::swap(a._servInfo, b._servInfo);
	std::swap(a._req, b._req);
	swap(a._staLine, b._staLine);
	std::swap(a._headers, b._headers);
	std::swap(a._body, b._body);
}

