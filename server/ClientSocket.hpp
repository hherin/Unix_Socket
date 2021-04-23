/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:02:08 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/23 15:25:38 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <iostream>
#include <string>
#include <exception>

class ClientSocket
{
	private:

		int	_fd;
		std::string _request;
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
		const std::string& getRequest() const;

		// Return response
		const std::string& getResponse() const;
	
		int receiveRequest(const char* buffer);
	
	private:

		friend void swap(ClientSocket& a, ClientSocket& b);
}; // class ClientSocket

#endif