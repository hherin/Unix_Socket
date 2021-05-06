/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:32:36 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/06 13:00:43 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BODY_HPP
#define BODY_HPP

#include "../../includes/webserv.hpp"

class Body
{
	private:

		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */
		
			bool								_recv;
			size_t								_size;
			std::string							_buff;


	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		Body() : _recv(false), _size() {}
		Body(const Body& c) :
				_recv(c._recv), _size(c._size), _buff(c._buff) {}
		~Body() {}
		Body& operator=(Body a)
		{
			swap(*this, a);
			return *this;
		}
		
		
		/* ------------------------------------------------------------- */
		/* --------------------------- GETTERS ------------------------- */

		const std::string& getBody() const { return _buff; }
		size_t getSize() const { return _size; }


		/* ------------------------------------------------------------- */
		/* --------------------------- SETTERS ------------------------- */
		
		void setSize(size_t size) { _size = size; }
		void startReceiving() { _recv = true; }


		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

		bool isReceiving() const { return _recv; }
		void clear()
		{
			_recv = false;
			_size = 0;
			_buff.clear();
		}
		void recvBuffer(const std::string& buffer, size_t index, size_t lenToRead)
		{
			_buff.append(buffer, index, _size);
			_size -= lenToRead;
		}
		
		
		/* ------------------------------------------------------------- */
		/* --------------- NON-MEMBER FUNCTION OVERLOADS --------------- */

		friend void swap(Body& a, Body& b)
		{
			std::swap(a._recv, b._recv);
			std::swap(a._size, b._size);
			std::swap(a._buff, b._buff);
		}
		
}; // class Body

#endif