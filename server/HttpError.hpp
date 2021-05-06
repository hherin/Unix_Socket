/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpError.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:32:17 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/04 14:06:46 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPERROR_HPP
#define HTTPERROR_HPP

#include "../includes/webserv.hpp"

class HttpError : public std::exception
{
	private:

		int		_code;

	public:

		HttpError(int code, const std::string& path) : std::runtime_error(path), _code(code) {};
		virtual const char* what() const throw()
		{
			std::cerr << ""
		}
		
}; // class HttpError

#endif