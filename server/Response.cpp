/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:23:57 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/26 18:37:58 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"


// apres avoir fait une requete, est ce que l'on close ?

/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

Response::Response() {}

Response::Response(Request* req, const StatusLine& staLine, std::vector<ServerInfo>* servInfo) :
	_servInfo(servInfo), _req(req), _staLine(staLine) {}

Response::Response(const Response& c) : 
	_servInfo(c._servInfo), _req(c._req), _staLine(c._staLine), _body(c._body) {}

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
	_body.clear();
	_buffer.clear();
}

void Response::fillBuffer()
{
	// Storing status line in buffer
	_buffer = "HTTP/1.1 " + convertNbToString(_staLine.getCode()) + " " + _staLine.getReason();
	if (!_staLine.getAdditionalInfo().empty())
		_buffer += " (" + _staLine.getAdditionalInfo() + ")";
	_buffer += CLRF;

	// Storing headers in buffer
	fillServerHeader();
	fillDateHeader();
	
	if (_req->getMethod() == GET)
	{
		// Looking for the location block matching the URI. If returns NULL, then no appropriate block was found
		// and no additionnal configuration (index, root...) will change the URI
		const Location* loc = locationSearcher(_servInfo,
				std::pair<std::string, std::string>(_req->getHeaders().find("host")->second, _req->getPath()));
		
		FileParser body(reconstructFullURI(loc).c_str(), true); // CAHNGER

		// Setting size after storing the body in FileParser object
		fillContentLenghtHeader(convertNbToString(body.getRequestFileSize()));
		_buffer += CLRF;

		// Writing the body previously stored to the buffer
		_buffer += body.getRequestFile();

		
	}
	else
	{
		fillContentLenghtHeader(convertNbToString(0));
		_buffer += CLRF;
	}

	std::cerr << "size to send: " << _buffer.size() << "\n";

	// http://localhost:8080/Users/llefranc/Rendu/42cursus/Unix_Socket/htmlFiles/index.html
}

/* ------------------------------------------------------------- */
/* ----------------------- PRIVATE METHODS --------------------- */

void Response::setHeader(std::string e)
{
	_buffer += e + CLRF;
}

void Response::fillContentLenghtHeader(const std::string& size) 
{
	_buffer += "Content-Length: " + size + CLRF;
}

void Response::fillServerHeader() 
{
	_buffer += "Server: webserv\r\n";
}

void Response::fillDateHeader() 
{
	// current date and time on the current system
	time_t now = time(0);

	// convert now to string form
	char* date_time = ctime(&now);

	// Splitting date line and removing '\n'
	std::vector<std::string> date = splitWithSep(date_time, ' ');
	date.back().resize(4);

	// Formating header date.
	// ctime format = Thu May 20 14:33:40 2021 >> to header date format : Thu, 20 May 2021 12:16:42 GMT
	_buffer += "Date: " + date[0] + ", " + date[2] + " " + date[1] + " " + date[4] + " " + date[3] + " GMT" + CLRF;
}

void printLoc(const Location* loc)
{
	std::cout << "root: " << loc->getRoot() << "\n";
	for (std::vector<std::string>::const_iterator it = loc->getMethods().begin(); it != loc->getMethods().end(); it++)
		std::cout << "methods: " << *it << "\n";
		
	for (std::vector<std::string>::const_iterator it = loc->getIndex().begin(); it != loc->getIndex().end(); it++)
		std::cout << "index: " << *it << "\n";

	std::cout << "autoindex: " << loc->getAutoIndex() << "\n";
}

const std::string& Response::reconstructFullURI(const Location* loc)
{
	std::cerr << "loc is null : " << loc << "\n";
	
	// zero location block match the URI so the URI isn't modified
	if (!loc)
		return _req->getPath();

	printLoc(loc);


	exit(1);

	return _req->getPath(); // A SUPPRIMER
}


/* ------------------------------------------------------------- */
/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

void swap(Response& a, Response& b)
{
	std::swap(a._servInfo, b._servInfo);
	std::swap(a._req, b._req);
	swap(a._staLine, b._staLine);
	std::swap(a._body, b._body);
}

