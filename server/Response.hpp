/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:14:47 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/03 14:42:28 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "Request.hpp"

class Response : public Request
{
	
	private:
	
		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		struct statusLine
		{
			int			_code;
			std::string _reason;

			statusLine() : _code(), _reason() {}
			statusLine(const statusLine& copy) :
					_code(copy._code), _reason(copy._reason) {}
			~statusLine() {}
		};

		struct statusLine					_staLine;	// Fist line of http response
		std::map<std::string, std::string>	_headers;	// Headers of http response
		std::string							_body;		// Body (= webpage content for example)
	
	
	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		Response();
		Response(const Response& copy);
		~Response();
		Response& operator=(Response assign);

	private:

		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */
		
		friend void swap(Response& a, Response& b);
	
}; // class Response

#endif