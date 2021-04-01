/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:53:22 by hherin            #+#    #+#             */
/*   Updated: 2021/04/01 14:56:55 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server() : _port(3490) 
{
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd < 0) {
		perror("ERROR opening socket");
		exit(1);
	}
	printf("Server-socket() is OK...\n");

	int yes = true;
	if(setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		perror("Server-setsockopt() error lol!");
		exit(1);
	}
	printf("Server-setsockopt() is OK...\n");

	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(_port);
	
	if (bind(_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		exit(1);
	}
	printf("Server-bind() is OK...\n");


	listen(_sockfd,5);
	printf("Server-listen() is OK...\n");
}

struct timeval*	setTimeval()
{
	static struct timeval tv;			// bc error without static (declared on stack and automatically release at end function)
	tv.tv_sec = 10;
	tv.tv_usec = 50000;
	return &tv;
}

void	Server::cliConnect()
{
	for (int i = 0; i < MAX_CONNECTIONS; i++)
		all_connections[i] = -1;
	all_connections[0] = _sockfd;

	while (true){
		FD_ZERO(&_readfd);
		FD_ZERO(&_writefd);

		for (int i = 0; i < MAX_CONNECTIONS; i++)
			if (all_connections[i] >= 0){
				FD_SET(all_connections[i], &_readfd);
				FD_SET(all_connections[i], &_writefd);
			}
		
		int selectval;
		// if ((selectval = select(FD_SETSIZE, &_readfd, &_writefd, NULL, setTimeval())) < 0){
		if ((selectval = select(FD_SETSIZE, &_readfd, NULL, NULL, setTimeval())) < 0){
			perror("ERROR on select");
			exit(1);
		}
		printf("RETOUR SELECT %d\n", selectval);
		if (selectval == 0){
			printf("TIMEOUT \n");
			exit(1);
		}
		else if (selectval >= 0){		 /* select() woke up. Identify the fd that has events */
			printf("Server-select() is OK...\n");

			if (FD_ISSET(_sockfd, &_readfd)){
				clilen = sizeof(cli_addr);
				bzero((char *) &cli_addr, sizeof(cli_addr));
				if ((_newsockfd = accept(_sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen)) < 0){
					perror("ERROR on accept");
					exit(1);
				}
				else{
					printf("Server-accept() is OK...\n");
					for (int i = 0; i < MAX_CONNECTIONS; i++){
						if (all_connections[i] < 0){
							all_connections[i] = _newsockfd;
							break;
						}
					}
				selectval--;
				if (!selectval) continue;
				}
			}

			/* Check if the fd with event is a non-server fd */
			for (int i = 1; i < MAX_CONNECTIONS; i++){
				if (all_connections[i] > 0 && FD_ISSET(all_connections[i], &_readfd)){
					printf("Returned fd is %d [index, i: %d]\n", all_connections[i], i);
					bzero(buffer,256);
					int n = recv(all_connections[i], buffer, 255, 0);
					if (n == 0){
						close(all_connections[i]);
						all_connections[i] = -1;
					}
					else if (n < 0) {
						perror("ERROR recv");
						exit(1);
					}
					else
						printf("Here is the message: %s\n\n",buffer); // call function that process the request
						
					// if (FD_ISSET(all_connections[i], &_writefd)){
						n = send(all_connections[i],"I got your message\n",19, 0);	// send the result
						if (n < 0) {
							perror("ERROR writing to socket");
							exit(1);
						}
						
					// }
					
				}
				selectval--;
				if (!selectval) continue;
			}

		}
	}
}