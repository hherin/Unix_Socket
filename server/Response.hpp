/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:14:47 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/06 17:57:44 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Request.hpp"
#include "msg_format/StatusLine.hpp"
#include "msg_format/Body.hpp"

#include "../parser/FileParser.hpp"

class Response
{
	private:
	
		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		// FileParser*							_readFile;
		Request								_req;	// Request object when the request is fully received

		StatusLine							_staLine;	// Fist line of http response
		std::map<std::string, std::string>	_headers;	// Headers of http response
		Body								_body;		// Body (= webpage content for example)
	
		std::string							_buffer;

	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		Response();
		Response(const Request& req, const StatusLine& staLine);
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
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */
		
		friend void swap(Response& a, Response& b);
	
}; // class Response

#endif