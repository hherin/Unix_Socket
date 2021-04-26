/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:39 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/23 18:23:27 by llefranc         ###   ########.fr       */
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

	if (posCLRF == std::string::npos) // checker peut etre la taille max ?
		return ;
	
	if (!_reqLine._method)
		parseStatusLine(posCLRF);
}

// Private

// A server can send a 505
//    (HTTP Version Not Supported)

// GET HEAD POST PUT DELETE

void Request::parseStatusLine(size_t posCLRF)
{
	// Checking that first line is not empty or contains whitespaces
	if (posCLRF == _index)
		throw "Error 400: bad request: first line is empty\n";

	std::string requestLine = _buffer.substr(_index, posCLRF - _index);
	
	if (requestLine.find_first_of("\r\n\t\v\f") != std::string::npos)
		throw "Error 400: bad request: whitespaces not allowed\n";
	
	// Splitting the request line
	std::vector<std::string> tokens;
	std::istringstream s(requestLine);

	while (std::getline(s, requestLine, ' '))
	{
		tokens.push_back(requestLine);
		if (tokens.size() > 3)
			throw "Error 400: bad request: too many spaces";
	}

	parseMethodToken(tokens[0]);

}

void Request::parseMethodToken(const std::string& token) const
{
	std::string methods[5] = {"GET", "HEAD", "PUT", "POST", "DELETE"};
	
	for (int i = 0; i < 5; ++i)
		if (!token.compare(_index, methods[i].size(), methods[i]))
			return ;

	throw "Error 501: not implemented\n";
}

void swap(Request& a, Request& b)
{
	std::swap(a._buffer, b._buffer);
}
