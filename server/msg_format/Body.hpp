/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:32:36 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/06/04 17:54:14 by llefranc         ###   ########.fr       */
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
		
			bool								_recv;		// Indicates when request line + headers have been received
			size_t								_size;		// Content-lenght size
			size_t								_maxSize;	// Max octets that Body object can receive
			std::string							_buff;		// Buffer containing the payload


	public:

		/* ------------------------------------------------------------- */
		/* ------------------------ COPLIEN FORM ----------------------- */

		Body() : _recv(false), _size(), _maxSize() {}
		Body(const Body& c) :
				_recv(c._recv), _size(c._size), _maxSize(c._maxSize), _buff(c._buff) {}
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
		size_t getMaxSize() const { return _maxSize; }


		/* ------------------------------------------------------------- */
		/* --------------------------- SETTERS ------------------------- */
		
		void setSize(size_t size) { _size = size; }
		void setMaxSize(size_t maxSize) { _maxSize = maxSize; }
		void setBuff(std::string const &buf) { _buff = buf; }
		void startReceiving() { _recv = true; }


		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

		// Returns true or false depending if request line + all headers have been received
		bool isReceiving() const { return _recv; }
		
		// Reset the Body object
		void clear()
		{
			_recv = false;
			_size = 0;
			_buff.clear();
		}
		
		// Append buffer received from client until content-lenght octets have been received
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
			std::swap(a._maxSize, b._maxSize);
			std::swap(a._buff, b._buff);
		}
		
}; // class Body

#endif