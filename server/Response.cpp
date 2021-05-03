/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:23:57 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/03 15:06:30 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"


/* ------------------------------------------------------------- */
/* ------------------------ COPLIEN FORM ----------------------- */

Response::Response() :
	Request(), _staLine(), _headers(), _body() {}

Response::~Response() {}

Response::Response(const Response& c) : Request(c), 
	_staLine(c._staLine), _headers(c._headers), _body(c._body) {}

Response& Response::operator=(Response a)
{
	swap(a, *this);
	return *this;
}


/* ------------------------------------------------------------- */
/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

void swap(Response& a, Response& b)
{
	swap(static_cast<Request&>(a), static_cast<Request&>(b));
	
	std::swap(a._staLine._code, b._staLine._code);
	std::swap(a._staLine._reason, b._staLine._reason);

	std::swap(a._headers, b._headers);
	
	std::swap(a._body, b._body);
}
