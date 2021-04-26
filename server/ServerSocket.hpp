/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:56:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/14 15:27:04 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <iostream>
#include <string>
#include <exception>

#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet itoa
#include <sys/time.h>

#include "../includes/webserv.hpp"

class ServerSocket
{
	private:

		int _port;
		int _maxClient;
		int	_fd;

	public:

		// Initialize variables
		ServerSocket(int port, int maxClient);
		~ServerSocket();

		ServerSocket(const ServerSocket& copy);
		ServerSocket& operator=(ServerSocket assign);
		
		// Return socket file descriptor
		int getFd() const;
		
		// Create a TCP socket listening on a specific port for x clients
		void createSocket();
	
	private:

		friend void swap(ServerSocket& a, ServerSocket& b);

}; // class ServerSocket

#endif