/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:39 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/20 13:53:35 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"


/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

Request::Request() :
	_index() {}

Request::~Request() {}

Request::Request(const Request& c) :
	_buffer(c._buffer), _index(c._index), _reqLine(c._reqLine), 
	_headers(c._headers),  _body(c._body) {}

Request& Request::operator=(Request a)
{
	swap(a, *this);
	return *this;
}
	

/* ------------------------------------------------------------- */
/* --------------------------- GETTERS ------------------------- */	

const RequestLine& Request::getRequestLine() const						{ return _reqLine; }

const std::map<std::string, std::string>& Request::getHeaders() const	{ return _headers; }

const Body& Request::getBody() const									{ return _body; }

const std::string& Request::getBuffer() const							{ return _buffer; }

int Request::getMethod() const											{ return _reqLine.getMethod(); }

const std::string& Request::getPath() const								{ return _reqLine.getPath(); }

const std::string& Request::getQuery() const							{ return _reqLine.getQuery(); }


/* ------------------------------------------------------------- */
/* --------------------------- METHODS ------------------------- */
	
Request& Request::operator+=(const char* charBuffer)
{
	_buffer += charBuffer;
	return *this;
}

void Request::parsingCheck()
{
    // Indicates end of request line / header line
	size_t posCLRF;
	posCLRF = !_body.isReceiving() ? _buffer.find(CLRF, _index) : 0;

    while (!_body.isReceiving() && newLineReceived(posCLRF))
    {
        if (_reqLine.empty())
            parseRequestLine(posCLRF);    
        
        // Double CRLF indicates end of headers
        else if (!_body.isReceiving() && _index == posCLRF)
		{
			_index += CLRF_OCTET_SIZE;
			
			std::map<std::string, std::string>::iterator contLen = _headers.find("content-lenght");

			if (contLen == _headers.end())
				throw StatusLine(400, REASON_400, "no content lenght header");
            _body.startReceiving();
			_body.setSize(atol(contLen->second.c_str()));
		}
            
        else if (!_body.isReceiving())
            parseHeaderLine(posCLRF);
            
        _index = posCLRF + CLRF_OCTET_SIZE;
        posCLRF = _buffer.find(CLRF, _index);
    }

	if (_body.isReceiving())
		parseBody();
}

void Request::clear()
{
	_index = 0;
	_buffer.clear();
	
	_reqLine.clear();
	_headers.clear();
	_body.clear();
}


/* ------------------------------------------------------------- */
/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */

void Request::parseBody()
{
	size_t lenToRead = _buffer.size() - _index;
	
	// Ignoring end of buffer if we received the amount of octets expected
	if (lenToRead > _body.getSize())
		_body.setSize(lenToRead);
	
	// Storing the part of body received until content-lenght octects are received
	_body.recvBuffer(_buffer, _index, lenToRead);
	_index += lenToRead;

	if (!_body.getSize())
	{
		std::cerr << "\n" << _body.getBody() << "\n----------\n";
		throw StatusLine(200, REASON_200);
	}
}

bool Request::newLineReceived(size_t posCLRF)
{
    // Protecting against too long fields
    if (_reqLine.getPath().empty() && _buffer.size() - _index > MAX_URI_LEN)
        throw StatusLine(414, REASON_414);
    else if (!_body.isReceiving() && _buffer.size() - _index > MAX_HEADER_LEN)
        throw StatusLine(431, REASON_431);

	else if (posCLRF == std::string::npos)
		return false;

    return true;
}

void Request::parseHeaderLine(size_t posCLRF)
{
    std::string headerLine = _buffer.substr(_index, posCLRF - _index);
    
	size_t pos = headerLine.find(":");
    if (pos == std::string::npos)
		throw StatusLine(400, REASON_400, "no semicolon");
	
	// Splitting field name and field value with first semicolon
	std::pair<std::string, std::string> headerField(headerLine.substr(0, pos), 
			headerLine.substr(pos + 1, std::string::npos));
	
	if (headerField.first.find_first_of("\r\n\t\v\f ") != std::string::npos)
		throw StatusLine(400, REASON_400, "no whitespaces before semicolon");
	
	// Header field name is case insensitive, transforming it to lowercase
    std::transform(headerField.first.begin(), headerField.first.end(), 
			headerField.first.begin(), asciiToLower);
	
	// Remove leading / trailing whitespaces in header field value
	headerField.second.erase(0, headerField.second.find_first_not_of(" \t"));
	headerField.second.erase(headerField.second.find_last_not_of(" \t") + 1, std::string::npos);
	
	if (!_headers.insert(headerField).second)
		throw StatusLine(400, REASON_400, "duplicated headers are not allowed");
    
    std::cerr << headerField.first << ":|" << headerField.second << "|\n"; // TEST
}

void Request::parseRequestLine(size_t posCLRF)
{
	// Checking that first line is not empty or contains whitespaces
	if (posCLRF == _index)
		throw StatusLine(400, REASON_400, "first line is empty");

	std::string requestLine = _buffer.substr(_index, posCLRF - _index);
	
	if (requestLine.find_first_of("\r\n\t\v\f") != std::string::npos)
		throw StatusLine(400, REASON_400, "whitespaces not allowed");
	else if (std::count(requestLine.begin(), requestLine.end(), ' ') > 2)
		throw StatusLine(400, REASON_400, "too many spaces");
	
	
	// Splitting the request line
	std::vector<std::string> tokens;
	std::istringstream s(requestLine);

	while (std::getline(s, requestLine, ' '))
		tokens.push_back(requestLine);
		
	if (tokens.size() != 3)
		throw StatusLine(400, REASON_400, "a field from request line is missing");


	// Parsing the request line
	parseMethodToken(tokens[0]);
	parseURI(tokens[1]);
	parseHTTPVersion(tokens[2]);

    std::cerr << _reqLine << "\n";
}

void Request::parseMethodToken(const std::string& token)
{
	std::string methods[5] = {"GET", "HEAD", "PUT", "POST", "DELETE"};
	
	for (int i = 0; i < 5; ++i)
	{
		// Token should exactly match one of the five methods
		if (!token.compare(_index, methods[i].size(), methods[i]) &&
				token.size() == methods[i].size())
		{
			_reqLine.setMethod(i);
			return ;
		}
	}

	throw StatusLine(400, REASON_400, "unknown method");
}

void Request::parseURI(std::string token)
{
	if (token[0] != '/')
		throw StatusLine(400, REASON_400, "URI must begin with a /");
	
    // URI is case insensitive, transforming it to lowercase
    std::transform(token.begin(), token.end(), token.begin(), asciiToLower);
    
	// Case there is a query in the URI
	size_t querryChar = token.find("?");
	if (querryChar != std::string::npos)
	{
		_reqLine.setPath(token.substr(0, querryChar));
		_reqLine.setQuery(token.substr(querryChar + 1, token.size()));
	}

	// Case there is only path in the URI
	else
		_reqLine.setPath(token);
}

void Request::parseHTTPVersion(const std::string& token)
{   
	if (token.compare(0, 5, "HTTP/") || token.compare(6, 1, ".") ||
			!isdigit(static_cast<int>(token[5])) || !isdigit(static_cast<int>(token[7])))
		throw StatusLine(400, REASON_400, "HTTP version not correct");
			
	else if (token.compare("HTTP/1.1"))
		throw StatusLine(505, REASON_505);
}


/* ------------------------------------------------------------- */
/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

void swap(Request& a, Request& b)
{
	std::swap(a._buffer, b._buffer);
	std::swap(a._index, b._index);
	
	swap(a._reqLine, b._reqLine);
	std::swap(a._headers, b._headers);
	swap(a._body, b._body);
}
