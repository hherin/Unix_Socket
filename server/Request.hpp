/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:06:51 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/23 18:23:18 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>

class Request
{
	private:

		struct requestLine
		{
			int _method;
			std::string _uri;
		};

		std::string _buffer;
		size_t _index;
		struct requestLine _reqLine;
	
	public:

		Request();
		~Request();

		Request(const Request& copy);
		Request& operator=(Request assign);

		Request& operator+=(const char* charBuffer);

		void parsingCheck();
	
	private:

		friend void swap(Request& a, Request& b);

		void parseStatusLine(size_t posCLRF);
		void parseMethodToken(const std::string& token) const;
		
}; // class Request

#endif