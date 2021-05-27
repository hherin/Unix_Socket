/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:23:57 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/27 18:03:21 by llefranc         ###   ########.fr       */
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
	_servInfo(c._servInfo), _req(c._req), _staLine(c._staLine), _body(c._body), _buffer(c._buffer) {}

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
	// Storing status line and some headers in buffer
	fillStatusLine(_staLine);
	fillServerHeader();
	fillDateHeader();
	
	if (_staLine.getCode() >= 300)
		return ;

	try
	{
		// Keeping only host name and removing port
		std::string hostName(_req->getHeaders().find("host")->second);
		hostName = hostName.substr(0, hostName.find(':'));
		
		// Looking for the location block matching the URI. If returns NULL, then no appropriate block was found
		// and no additionnal configuration (index, root...) will change the URI
		std::pair<const std::string, const Location*> loc = locationSearcher(_servInfo,
				std::pair<std::string, std::string>(hostName, _req->getPath()));
			
		std::string realUri = reconstructFullURI(_req->getMethod(), loc, _req->getPath()); 
			
		if (_req->getMethod() == GET || _req->getMethod() == HEAD)
		{
			FileParser body(realUri.c_str(), true); // CAHNGER

			// Setting size after storing the body in FileParser object
			fillContentLenghtHeader(convertNbToString(body.getRequestFileSize()));
			_buffer += CLRF;

			// For GET, writing the body previously stored to the buffer
			// _req->getMethod() == GET ? _buffer += body.getRequestFile() : 0;
			if (_req->getMethod() == GET)
				_buffer += body.getRequestFile();
		}

		else
		{
			fillContentLenghtHeader(convertNbToString(0));
			_buffer += CLRF;
		}
	}

	catch (const StatusLine& errorStaLine)
	{
		fillStatusLine(errorStaLine);
		fillServerHeader();
		fillDateHeader();
	}

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

void Response::fillStatusLine(const StatusLine& staLine)
{
	_buffer = "HTTP/1.1 " + convertNbToString(staLine.getCode()) + " " + staLine.getReason();
	if (!staLine.getAdditionalInfo().empty())
		_buffer += " (" + staLine.getAdditionalInfo() + ")";
	_buffer += CLRF;
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

void Response::addRoot(std::string* uri, const std::string& root, const std::string& locName)
{
	// Creating an iterator pointing just after the part that matched the location
	std::string::iterator it = uri->begin() + locName.size();

	// Going to the next '/' (for example, case "/authentificate/ok" matched location "/auth" with a root of "/test"
	//						  >> we need to replace "/authentificate" with "/test" in order to get "/test/ok")
	if (*it != '/')
		while (*it && *it != '/')
			++it;
	
	// Replacing beginning of the URI with the root path
	uri->erase(uri->begin(), it);
	
	// To correctly append indexs if last '/' is missing
	if (root.back() != '/')
		uri->insert(uri->begin(), '/');
		
	uri->insert(0, root);
}

std::string Response::addIndex(const std::string& uri, const std::vector<std::string>& indexs)
{
	struct stat infFile;
	
	for (std::vector<std::string>::const_iterator it = indexs.begin(); it != indexs.end(); ++it)
	{
		std::string uriWithIndex(uri + *it);

		std::cerr << "TRYING URI + INDEX: |" << uriWithIndex << "\n";

		if (!stat(uriWithIndex.c_str(), &infFile))
			return uriWithIndex;
	}
	
	throw StatusLine(301, REASON_301, "trying to access a directory");
}

void Response::checkMethods(int method, const std::vector<std::string>& methodsAllowed) const
{
	std::string tab[5] = { "GET", "HEAD", "PUT", "POST", "DELETE" };

	std::cout << "le numero de method = " << method << "\n";

	for (std::vector<std::string>::const_iterator it = methodsAllowed.begin();
			it != methodsAllowed.end(); ++it)
	{
		std::cerr << "mthod = |" << tab[method] << "| && la mehode comparee = |" << *it << "|\n";
		if (!it->compare(tab[method]))
			return ;
	}

	throw StatusLine(405, REASON_405);
}

std::string Response::reconstructFullURI(int method,
		const std::pair<const std::string, const Location*>& loc, std::string uri)
{
	struct stat infFile;

	// zero location block match the URI so the URI isn't modified
	if (!loc.second)
	{
		// Checking if the file exist or if it's  directory
		if (stat(uri.c_str(), &infFile) == -1)
			throw StatusLine(404, REASON_404);
		if (S_ISDIR(infFile.st_mode))
			throw StatusLine(301, REASON_301, "trying to access a directory");

		return uri;
	}

	// Replacing the part of the URI that matched with the root path if there is one existing
	if (!loc.second->getRoot().empty())
		addRoot(&uri, loc.second->getRoot(), loc.first);

	if (stat(uri.c_str(), &infFile) == -1)
		throw StatusLine(404, REASON_404, "stat retruned -1 in reconstruct");
	if (S_ISDIR(infFile.st_mode))
		uri = addIndex(uri, loc.second->getIndex());
	
	printLoc(loc.second);
	
	checkMethods(method, loc.second->getMethods());
	/*
	dans l'ordre:
	- on ajoute le root
	- on check ensuite si c'est un directory ou pas
	- si c'est un directory, on essaye d'append chaque index et de voir si un fichier existe
	- si un fichier avec ce chemin existe, on relance une recherche du bon bloc location avec cette uri
	*/

	// printLoc(loc.second);
	// exit(1);

	return uri;
}


/* ------------------------------------------------------------- */
/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

void swap(Response& a, Response& b)
{
	std::swap(a._servInfo, b._servInfo);
	std::swap(a._req, b._req);
	swap(a._staLine, b._staLine);
	std::swap(a._body, b._body);
	std::swap(a._buffer, b._buffer);
}
