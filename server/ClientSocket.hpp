/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:02:08 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/26 13:53:42 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <iostream>
#include <string>
#include <exception>

#include "Request.hpp"
#include "../includes/webserv.hpp"

class ClientSocket
{
	private:

		int	_fd;
		Request _request;
		std::string _response;

	public:

		// Initialize variables
		ClientSocket(int fd);
		~ClientSocket();
		
		ClientSocket(const ClientSocket& copy);
		ClientSocket& operator=(ClientSocket assign);

		// Return socket id
		int getFd() const;

		// Return request
		const Request& getRequest() const;

		// Return response
		const std::string& getResponse() const;
	
		int receiveRequest(const char* buffer);
	
	private:

		friend void swap(ClientSocket& a, ClientSocket& b);
		
}; // class ClientSocket

#endif