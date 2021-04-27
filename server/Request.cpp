/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:39 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/27 14:04:06 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request()
	: _buffer(), _index(), _reqLine(), _headers(), _recvBody(0), _body() {}

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
    // Indicates end of request line / header line
	size_t posCLRF = _buffer.find("\r\n", _index);

    // Protecting against too long fields
    if (!_reqLine._method && posCLRF > MAX_URI_LEN)
        throw "Error 414: request URI too long\n";
    else if (posCLRF - _index > MAX_HEADER_LEN)
        throw "Error 431: request header fields too large\n";

	else if (posCLRF == std::string::npos)
		return ;
    
    // Treating request line
	else if (!_reqLine._method)
    {
		parseRequestLine(posCLRF);
        _index += posCLRF + 2;
    }
    
    // Treating header fields
    while ((posCLRF = _buffer.find("\r\n", _index)) != std::string::npos)
    {
        // Double endLine indicates that request line + headers fields have been received
        if (_buffer.find("\r\n", posCLRF + 2) == posCLRF + 2)
        {
            _recvBody = true;
            break;
        }

        parseHeaderField(posCLRF);
        _index += posCLRF + 2;
    }
}

// Private


void Request::parseHeaderField(size_t posCLRF)
{
    std::string headerLine = _buffer.substr(_index, posCLRF - _index);
    
    if (headerLine.find(":") == std::string::npos)
		throw "Error 400: bad request: whitespaces not allowed\n";
}

// Parsing request line

void Request::parseRequestLine(size_t posCLRF)
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


	// Parsing the request line
	parseMethodToken(tokens[0]);
	parseURI(tokens[1]);
	parseHTTPVersion(tokens[2]);
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

void Request::parseURI(std::string token)
{
	if (token[0] != '/')
		throw "Error 400: bad request: URI must begin with a /\n";
	
    // URI is case insensitive, transforming it to lowercase
    std::transform(token.begin(), token.end(), token.begin(), asciiToLower);
    
	// Case there is a query in the URI
	size_t querryChar = token.find("?");
	if (querryChar != std::string::npos)
	{
		_reqLine._path = token.substr(0, querryChar);
		_reqLine._query = token.substr(querryChar + 1, token.size());
	}

	// Case there is only path in the URI
	else
		_reqLine._path = token;
}

void Request::parseHTTPVersion(const std::string& token)
{   
	if (token.compare(0, 5, "HTTP/") || token.compare(6, 1, ".") ||
			!isdigit(static_cast<int>(token[5])) || !isdigit(static_cast<int>(token[7])))
		throw "Error 400: bad request: HTTP version not correct\n";
			
	else if (token.compare("HTTP/1.1"))
		throw "Error 505: HTTP Version Not Supported\n";
}

void swap(Request& a, Request& b)
{
	std::swap(a._buffer, b._buffer);
}
