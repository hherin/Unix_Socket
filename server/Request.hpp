/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:51 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/02 20:46:38 by lucaslefran      ###   ########.fr       */
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

class Request
{
	private:

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

		struct msgBody
		{
			bool								_recv;
			size_t								_size;
			std::string							_buff;

			msgBody() : _recv(), _size(), _buff() {}
			msgBody(const msgBody& c) :
					_recv(c._recv), _size(c._size), _buff(c._buff) {}
			~msgBody() {}
		};

		std::string	_buffer;
		size_t		_index;
        
		struct requestLine					_reqLine;
        std::map<std::string, std::string>	_headers;
        struct msgBody						_body;
	
	public:

		Request();
		Request(const Request& copy);
		~Request();

		Request& operator=(Request assign);
		Request& operator+=(const char* charBuffer);

		void parsingCheck();
	
	private:

		friend void swap(Request& a, Request& b);

        bool newLineReceived(size_t posCLRF);

		void parseRequestLine(size_t posCLRF);
		void parseMethodToken(const std::string& token);
		void parseURI(std::string token);
		void parseHTTPVersion(const std::string& token);
        
        void parseHeaderLine(size_t posCLRF);
		
		void parseBody();
}; // class Request

#endif