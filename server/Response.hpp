/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:14:47 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/20 13:40:18 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

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

		std::vector<ServerInfo>				_servInfo;	// Servers blocks from config file that match a specific port
		Request								_req;		// Request object when the request is fully received

		StatusLine							_staLine;	// Fist line of http response
		std::map<std::string, std::string>	_headers;	// Headers of http response
		Body								_body;		// Body (= webpage content for example)
	
		std::string							_buffer;	// Buffer containing the response that will be send

	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		Response();
		Response(const Request& req, const StatusLine& staLine, const std::vector<ServerInfo>& servInfo);
		Response(const Response& c);
		~Response();
		Response& operator=(Response a);

		
		/* ------------------------------------------------------------- */
		/* --------------------------- SETTERS ------------------------- */

		void setRequest(const Request& req);
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


		/* ------------------------------------------------------------- */
		/* ----------------------- PRIVATE METHODS --------------------- */

	private:

		void execGET();

		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */
		
	public:

		friend void swap(Response& a, Response& b);
	
}; // class Response

#endif