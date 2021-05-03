/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:39 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/02 20:48:14 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request() :
	_buffer(), _index(), _reqLine(), _headers(), _body() {}

Request::~Request() {}

Request::Request(const Request& copy) :
	_buffer(copy._buffer), _index(copy._index), _reqLine(copy._reqLine), 
	_headers(copy._headers),  _body(copy._body) {}

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
	size_t posCLRF;
	posCLRF = !_body._recv ? _buffer.find(CLRF, _index) : 0;

    while (!_body._recv && newLineReceived(posCLRF))
    {
        if (_reqLine._path.empty())
            parseRequestLine(posCLRF);    
        
        // Double CRLF indicates end of headers
        else if (!_body._recv && _index == posCLRF)
		{
			_index += CLRF_OCTET_SIZE;
			
			std::map<std::string, std::string>::iterator contLen = _headers.find("content-lenght");

			if (contLen == _headers.end())
				throw "Error 400: bad request: no content lenght header\n"; // rajouter trnafer encoding + head etc + get n'a pas de body ?
            _body._recv = true;
			_body._size = atol(contLen->second.c_str());
		}
            
        else if (!_body._recv)
            parseHeaderLine(posCLRF);
            
        _index = posCLRF + CLRF_OCTET_SIZE;
        posCLRF = _buffer.find(CLRF, _index);
    }

	if (_body._recv)
		parseBody();
}

// Private

void Request::parseBody()
{
	size_t lenToRead = _buffer.size() - _index;
	
	// Ignoring end of buffer if we received the amount of octets expected
	if (lenToRead > _body._size)
		lenToRead = _body._size;
	
	// Storing the part of body received until content-lenght octects are received
	_body._buff.append(_buffer, _index, _body._size);
	_index += lenToRead;
	_body._size -= lenToRead;

	if (!_body._size)
	{
		std::cerr << "\n" << _body._buff << "\n----------\n";
		exit(EXIT_SUCCESS);
		
		// ICI LANCER SUREMENT LA REPONSE. REPRENDRE A CE STADE.
	}
}

bool Request::newLineReceived(size_t posCLRF)
{
    // Protecting against too long fields
    if (_reqLine._path.empty() && _buffer.size() - _index > MAX_URI_LEN)
        throw "Error 414: request URI too long\n";
    else if (!_body._recv && _buffer.size() - _index > MAX_HEADER_LEN)
        throw "Error 431: request header fields too large\n";

	else if (posCLRF == std::string::npos)
		return false;

    return true;
}

void Request::parseHeaderLine(size_t posCLRF)
{
    std::string headerLine = _buffer.substr(_index, posCLRF - _index);
    
	size_t pos = headerLine.find(":");
    if (pos == std::string::npos)
		throw "Error 400: bad request: no semicolon\n";
	
	// Splitting field name and field value with first semicolon
	std::pair<std::string, std::string> headerField(headerLine.substr(0, pos), 
			headerLine.substr(pos + 1, std::string::npos));
	
	if (headerField.first.find_first_of("\r\n\t\v\f ") != std::string::npos)
		throw "Error 400: bad request: no whitespaces before semicolon\n";
	
	// Header field name is case insensitive, transforming it to lowercase
    std::transform(headerField.first.begin(), headerField.first.end(), 
			headerField.first.begin(), asciiToLower);
	
	// Remove leading / trailing whitespaces in header field value
	headerField.second.erase(0, headerField.second.find_first_not_of(" \t"));
	headerField.second.erase(headerField.second.find_last_not_of(" \t") + 1, std::string::npos);
	
	if (!_headers.insert(headerField).second)
		throw "Error 400: bad request: duplicated headers are not allowed\n";
    
    std::cerr << headerField.first << ":|" << headerField.second << "|\n"; // TEST
}

// PARSING REQUEST LINE

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

    std::cerr << _reqLine._method << " " << _reqLine._path; // TEST
    _reqLine._query.empty() ? std::cerr << "\n" : std::cerr << "?" << _reqLine._query << "\n"; // TEST
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
	std::swap(a._index, b._index);
	
	std::swap(a._reqLine._method, b._reqLine._method);
	std::swap(a._reqLine._path, b._reqLine._path);
	std::swap(a._reqLine._query, b._reqLine._query);

	std::swap(a._headers, b._headers);

	std::swap(a._body._recv, b._body._recv);
	std::swap(a._body._size, b._body._size);
	std::swap(a._body._buff, b._body._buff);
}
