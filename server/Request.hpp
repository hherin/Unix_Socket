/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:51 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/06 12:43:47 by lucaslefran      ###   ########.fr       */
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
#include "msg_format/Body.hpp"

class Request
{
	private:

		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		struct requestLine
		{
			int			_method;
			std::string _path;
			std::string _query;

			requestLine() : _method(), _path(), _query() {}
			requestLine(const requestLine& c) :
					_method(c._method), _path(c._path), _query(c._query) {}
			~requestLine() {}
		};

		std::string	_buffer;
		size_t		_index;
        
		struct requestLine					_reqLine;
        std::map<std::string, std::string>	_headers;
        Body								_body;
	
	
	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		Request();
		Request(const Request& c);
		~Request();
		Request& operator=(Request a);
		

		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

		Request& operator+=(const char* charBuffer);
		void parsingCheck();
		void clear();
	
	private:

		/* ------------------------------------------------------------- */
		/* ------------------ PRIVATE MEMBER FUNCTIONS ----------------- */
		
        bool newLineReceived(size_t posCLRF);

		void parseRequestLine(size_t posCLRF);
		void parseMethodToken(const std::string& token);
		void parseURI(std::string token);
		void parseHTTPVersion(const std::string& token);
        
        void parseHeaderLine(size_t posCLRF);
		
		void parseBody();
		
		
		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */
		
		friend void swap(Request& a, Request& b);
		
}; // class Request

#endif