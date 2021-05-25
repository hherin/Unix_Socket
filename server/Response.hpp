/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:14:47 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/25 16:00:35 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <ctime>

#include "Request.hpp"
#include "msg_format/StatusLine.hpp"
#include "msg_format/Body.hpp"

#include "../parser/FileParser.hpp"
#include "../parser/ServerInfo.hpp"

class Response
{
	private:
	
		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		const std::vector<ServerInfo>*		_servInfo;	// Servers blocks from config file that match a specific port
		Request*							_req;		// Request object when the request is fully received, used to create response

		StatusLine							_staLine;	// Fist line of http response
		Body								_body;		// Body (= webpage content for example)
	
		std::string							_buffer;	// Buffer containing the response that will be send. Directly writing
														// headers into it.

	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		Response();
		Response(Request* req, const StatusLine& staLine, const std::vector<ServerInfo>* servInfo);
		Response(const Response& c);
		~Response();
		Response& operator=(Response a);

		
		/* ------------------------------------------------------------- */
		/* --------------------------- SETTERS ------------------------- */

		void setRequest(Request* req);
		void setStatusLine(const StatusLine& staLine);


		/* ------------------------------------------------------------- */
		/* --------------------------- GETTERS ------------------------- */
		
		const StatusLine& getStatusLine() const;
		int getCode() const;
		const std::string& getBuffer() const;
		

		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

		// Reset response object
		void clear();

		// Fill response buffer according to request object and status line previously set
		void fillBuffer();

		// Execute the appropriate method
		void execMethod();

		// Sets all the appropriate headers using request object and status line, both previously set
		void setHeaders();


	private:

		/* ------------------------------------------------------------- */
		/* ----------------------- PRIVATE METHODS --------------------- */

		void execGET();

		// Fills buffer with Content-lenght header
		void fillContentLenghtHeader(const std::string& size);

		// Fills buffer with server header with server name (webserv)
		void fillServerHeader();

		// Fills buffer with Date header with the actual date
		void fillDateHeader();


	public:
	
		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

		friend void swap(Response& a, Response& b);
	
}; // class Response

#endif