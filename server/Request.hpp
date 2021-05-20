/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:51 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/20 12:24:54 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <map>

#include "../includes/webserv.hpp"
#include "msg_format/StatusLine.hpp"
#include "msg_format/RequestLine.hpp"
#include "msg_format/Body.hpp"

class Request
{
	private:

		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		std::string	_buffer;	// Store the request received
		size_t		_index;		// Indicates which part of the buffer is left to treat
        
		RequestLine							_reqLine;	// Contains all the information from the request line
        std::map<std::string, std::string>	_headers;	// Store the headers
        Body								_body;		// Store the body
	
	
	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		Request();
		Request(const Request& c);
		~Request();
		Request& operator=(Request a);
		

		/* ------------------------------------------------------------- */
		/* --------------------------- GETTERS ------------------------- */

		const std::string& getBuffer() const;
		const RequestLine& getRequestLine() const;
		const std::map<std::string, std::string>& getHeaders() const;
		const Body& getBody() const;

		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

		// Add the buffer from receive to request object
		Request& operator+=(const char* charBuffer);

		// Check if the data received is correct. If an error occur or if a request was
		// fully received, throws a status line with the appropriate code.
		void parsingCheck();

		// Reset the request object
		void clear();
	
	
	private:

		/* ------------------------------------------------------------- */
		/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */
		
		// Check if a new line was received (corresponding to a request line or an header).
		// If the request line is superior to MAX_URI_LEN or if an header line is superior 
		// to MAX_HEADER_LEN, throws a status line with the appropriate code.
        bool newLineReceived(size_t posCLRF);

		// Checks that the request line received respect the RFC norme.
		void parseRequestLine(size_t posCLRF);

		// Checks that the first word in a request line in a appropriate method.
		void parseMethodToken(const std::string& token);

		// Check that the URI in the request line respect the RFC norme.
		void parseURI(std::string token);

		// Check that the HTTP version in the request line is respecting the RFC norme and is equal 
		// to 1.1.
		void parseHTTPVersion(const std::string& token);
        
		// Check that the header line received respect the RFC norme.
        void parseHeaderLine(size_t posCLRF);
		
		// Received the body until n octets (from content-lenght header) has been received. Then throw 
		// a status line with the appropriate code.
		void parseBody();
		
		
		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */
		
		friend void swap(Request& a, Request& b);
		
}; // class Request

#endif