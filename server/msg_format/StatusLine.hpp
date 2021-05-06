/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusLine.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:40:02 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/06 12:01:42 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUSLINE_HPP
#define STATUSLINE_HPP

#include "../../includes/webserv.hpp"
#include "iostream"

class StatusLine
{
	private:
	
		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */
	
		int			_code;
		std::string _reason;
		std::string _addInfos; // Additionnal informations if an error occured for developpment and debug


	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		StatusLine() : _code(), _reason() {}
		StatusLine(int code, const char* reason, const std::string& addInfos = "") :
			_code(code), _reason(reason), _addInfos(addInfos) {}
		StatusLine(const StatusLine& c) :
				_code(c._code), _reason(c._reason), _addInfos(c._addInfos) {}
		~StatusLine() {}
		
		
		/* ------------------------------------------------------------- */
		/* --------------------------- GETTERS ------------------------- */

		int getCode() const { return _code; }
		const std::string& getReason() const { return _reason; }
		const std::string& getAdditionalInfo() const { return _addInfos; }


		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

		friend void swap(StatusLine& a, StatusLine& b)
		{
			std::swap(a._code, b._code);
			std::swap(a._reason, b._reason);
			std::swap(a._addInfos, b._addInfos);
		}
		
}; // class StatusLine


/* ------------------------------------------------------------- */
/* -------------------- OPERATOR OVERLOADS --------------------- */

inline std::ostream& operator<<(std::ostream& stream, const StatusLine& staLine)
{
	stream << staLine.getCode() << ": " << staLine.getReason();
	
	if (!staLine.getAdditionalInfo().empty())
		stream << ": " << staLine.getAdditionalInfo();
		
	return stream;
}

#endif