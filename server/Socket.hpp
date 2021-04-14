/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:56:29 by llefranc          #+#    #+#             */
/*   Updated: 2021/04/14 15:27:04 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

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

class Socket
{
	private:

		int _port;
		int	_acceptFd;
		int _maxClient;

	public:

		Socket(int port, int maxClient);
		~Socket();
		
		int getAcceptSocketFd() const;
		
		void createSocket();

}; // class Socket

#endif