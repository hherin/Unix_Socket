/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusLine.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:40:02 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/10 16:11:37 by llefranc         ###   ########.fr       */
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
	
		int			_code;		// Code indicating the response category (ex: 200 means ok)
		std::string _reason;	// Reason explaing the code
		std::string _addInfos;	// Additionnal informations if an error occured for developpment and debug


	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		StatusLine() : _code(-1), _reason() {}
		StatusLine(int code, const char* reason, const std::string& addInfos = "") :
			_code(code), _reason(reason), _addInfos(addInfos) {}
		StatusLine(const StatusLine& c) :
				_code(c._code), _reason(c._reason), _addInfos(c._addInfos) {}
		~StatusLine() {}
		StatusLine& operator=(StatusLine a)
		{
			swap(*this, a);
			return *this;
		}
		
		
		/* ------------------------------------------------------------- */
		/* --------------------------- GETTERS ------------------------- */

		int getCode() const { return _code; }
		const std::string& getReason() const { return _reason; }
		const std::string& getAdditionalInfo() const { return _addInfos; }


		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

		// Clear the StatusLine object
		void clear()
		{
			_code = -1;
			_reason.clear();
			_addInfos.clear();
		}
		

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