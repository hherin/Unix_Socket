/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:39 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/26 14:02:17 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request()
	: _buffer(), _index(), _reqLine() {}

Request::~Request() {}

Request::Request(const Request& copy)
	: _buffer(copy._buffer) {}

Request& Request::operator=(Request assign)
{
	swap(assign, *this);
	return *this;
}
	
Request& Request::operator+=(const char* charBuffer)
{
	_buffer += charBuffer;
	return *this;
}

void Request::parsingCheck()
{
	size_t posCLRF = _buffer.find("\r\n", _index);

	if (posCLRF == std::string::npos) // checker peut etre la taille max pour la request line et headers ?
		return ;
	
	if (!_reqLine._method)
		parseStatusLine(posCLRF);
}

// Private

// A server can send a 505
//    (HTTP Version Not Supported)

// pour uri >> on parse la path, elle s'arrete au premier ? ou #, ensuite on parse querry et fragment

// si url > 8000 414 Request-URI Too Long

// GET HEAD POST PUT DELETE

void Request::parseStatusLine(size_t posCLRF)
{
	// Checking that first line is not empty or contains whitespaces
	if (posCLRF == _index)
		throw "Error 400: bad request: first line is empty\n";

	std::string requestLine = _buffer.substr(_index, posCLRF - _index);
	
	if (requestLine.find_first_of("\r\n\t\v\f") != std::string::npos)
		throw "Error 400: bad request: whitespaces not allowed\n";
	else if (std::count(requestLine.begin(), requestLine.end(), ' ') > 2)
		throw "Error 400: bad request: too many spaces\n";
	
	
	// Splitting the request line
	std::vector<std::string> tokens;
	std::istringstream s(requestLine);

	while (std::getline(s, requestLine, ' '))
	{
		tokens.push_back(requestLine);
		if (tokens.size() > 3)
			throw "Error 400: bad request: too many spaces\n";
	}

	if (tokens.size() != 3)
		throw "Error 400: bad request: a field from request line is missing\n";

	std::cout << "size = " << tokens.size() << "\n";

	// Parsing the request line
	parseMethodToken(tokens[0]);
	parseURI(tokens[1]);
	parseHTTPVersion(tokens[2]);

	std::cout << "method = " << _reqLine._method
		<< ", PATH = " << _reqLine._path << ", QUERY = " << _reqLine._query << "\n";
}

void Request::parseMethodToken(const std::string& token)
{
	std::string methods[5] = {"GET", "HEAD", "PUT", "POST", "DELETE"};
	
	for (int i = 0; i < 5; ++i)
	{
		if (!token.compare(_index, methods[i].size(), methods[i]))
		{
			_reqLine._method = i;
			return ;
		}
	}

	throw "Error 400: bad request: unknown method\n";
}

void Request::parseURI(const std::string& token)
{
	if (token[0] != '/')
		throw "Error 400: bad request: URI must begin with a /\n";
	
	// Case there is a query in the URI
	size_t querryChar = token.find("?");
	if (querryChar != std::string::npos)
	{
		_reqLine._path = token.substr(0, querryChar);
		_reqLine._query = token.substr(querryChar, token.size());
	}

	// Only path is the URI
	else
		_reqLine._path = token;
}

void Request::parseHTTPVersion(const std::string& token)
{
	if (token.compare(0, 5, "HTTP/") || token.compare(7, 1, ".") ||
			!isdigit(static_cast<int>(token[5])) || !isdigit(static_cast<int>(token[7])))
		throw "Error 400: bad request: HTTP version not correct\n";
			
	else if (token.compare("HTTP/1.1"))
		throw "Error 505: HTTP Version Not Supported\n";
}

void swap(Request& a, Request& b)
{
	std::swap(a._buffer, b._buffer);
}
