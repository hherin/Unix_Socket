/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:32:36 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/21 13:45:07 by hherin           ###   ########.fr       */
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
		
			bool								_recv;	// Indicates when request line + headers have been received
			size_t								_size;	// Content-lenght size
			std::string							_buff;	// Buffer containing the body


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
			std::swap(a._buff, b._buff);
		}
		
}; // class Body

#endif