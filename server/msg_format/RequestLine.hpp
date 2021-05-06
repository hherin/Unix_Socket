/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestLine.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 16:51:26 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/06 16:57:43 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTLINE_HPP
#define REQUESTLINE_HPP

#include "../../includes/webserv.hpp"
#include <iostream>

class RequestLine
{
	private:
	
		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */
	
		int			_method;
		std::string _path;
		std::string _query;


	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		RequestLine() : _method(-1) {}
		RequestLine(const RequestLine& c) :
				_method(c._method), _path(c._path), _query(c._query) {}
		~RequestLine() {}
		RequestLine& operator=(RequestLine a)
		{
			swap(*this, a);
			return *this;
		}
		
		
		/* ------------------------------------------------------------- */
		/* --------------------------- GETTERS ------------------------- */

		int getMethod() const { return _method; }
		const std::string& getPath() const { return _path; }
		const std::string& getQuery() const { return _query; }


		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

		friend void swap(RequestLine& a, RequestLine& b)
		{
			std::swap(a._method, b._method);
			std::swap(a._path, b._path);
			std::swap(a._query, b._query);
		}
		
}; // class RequestLine


/* ------------------------------------------------------------- */
/* -------------------- OPERATOR OVERLOADS --------------------- */

inline std::ostream& operator<<(std::ostream& stream, const RequestLine& reqLine)
{
	stream << "Method = " << reqLine.getMethod() << ", path = |" << reqLine.getPath() << "|";
	
	if (!reqLine.getQuery().empty())
		stream << ", query = |" << reqLine.getQuery() << "|";
		
	return stream;
}
#endif