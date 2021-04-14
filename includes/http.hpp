/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   htpp.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:48:52 by hherin            #+#    #+#             */
/*   Updated: 2021/04/09 15:38:15 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef http_HPP
# define http_HPP

# include <sys/socket.h>
# include <stdlib.h>
# include <stdio.h>
# include <strings.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h> //inet itoa
# include <sys/time.h>
# include <string>

#define MAX_CONNECTIONS 10
#define TIMEOUT 10


class http
{
	public:
		http();
		
		void	cliConnect();

		~http() { close(_sockfd);	}

	private:
		std::string const	&recv_timeout(int &fd);
		void				request_handler();
		int					add_client();
		
		struct sockaddr_in serv_addr, cli_addr;
		int _port, _sockfd, _newsockfd;
		unsigned int clilen;
		char buffer[256];
		int all_connections[MAX_CONNECTIONS];
		fd_set _readfd;//, _writefd;
		std::string bufRecv;
		int selectval;
};



#endif

//  loin de moi l'idée de graver dans le marbre de tailler dans une écorce d'arbre loin de moi l'idée de suggérer que 
//  je m'en moque que je n'en ai rien à faire que guère je ne m'en soucie loin de moi ces folies mais je m'échine depuis 
//  octobre et pourquoi donc depuis début octobre même et qui m'aime me suive depuis octobre depuis ce même dernier octobre 
//  le trois du mois je crois depuis ce temps-là depuis trois mois depuis trois mois et une semaine je m'échine ailleurs et 
//  le très long texte n'a pas avancé d'un poil pas beaucoup sans doute est-ce mon côté velléitaire 
//  qui ne cesse de me jouer des tours et les méandres du très long texte se sont figés comme une gelée le long des parois 