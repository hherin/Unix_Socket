/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:48:52 by hherin            #+#    #+#             */
/*   Updated: 2021/04/01 14:15:14 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h> //inet itoa

#define MAX_CONNECTIONS 10

class Server
{
	public:
		Server();

		
		void	cliConnect();

		~Server() { close(_sockfd);	}

	private:
		struct sockaddr_in serv_addr, cli_addr;
		int _port, _sockfd, _newsockfd;
		unsigned int clilen;
		char buffer[256];
		int all_connections[MAX_CONNECTIONS];
		fd_set _readfd, _writefd;
};



#endif