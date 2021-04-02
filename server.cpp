/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:53:22 by hherin            #+#    #+#             */
/*   Updated: 2021/04/02 18:02:20 by hherin           ###   ########.fr       */
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

// try to loop in recv
std::string const &Server::recv_timeout(int &fd)
{
	char buffer[1000];
	int recvVal, totLen = 0;
	static std::string req;
	struct timeval begin, now;
	double timediff;
	
	req.clear();
	gettimeofday(&begin, NULL);
	
	while (1){
		gettimeofday(&now, NULL);
		timediff = (now.tv_sec - begin.tv_sec) + 1e-6 * (now.tv_usec - begin.tv_usec);

		if (totLen > 0 && timediff > TIMEOUT)
			break;
		else if (timediff > TIMEOUT * 2)	//if no data at all, wait a little longer twice timeout
			break;
		printf("1\n");
		bzero(buffer,256);
		if ((recvVal = recv(fd, buffer, 1000, 0)) < 0){
			perror("ERROR recv");
			exit(1);
		}
		else{
			printf("HEY\n");
			req.append(buffer);
			totLen += recvVal;
			gettimeofday(&begin, NULL);
		}
		printf("2\n");
	}

	return req;
}

/* Check if the fd with event is a non-server fd */
void	Server::request_handler()
{
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
				printf("Here is the message:\n %s\n\n",buffer); // call function that process the request

			// send msg to the client
			n = send(all_connections[i],"I got your message\n",19, 0);
			if (n < 0) {
				perror("ERROR writing to socket");
				exit(1);
			}
						
			if (!strncmp(bufRecv.c_str(), "close", 5))
			{
				close(all_connections[i]);
			}
			selectval--;
			if (!selectval) continue;
		}	
	}
}

int	Server::add_client()
{
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
			if (!selectval) return 1;
		}
	}
	return 0;
}

void	Server::cliConnect()
{
	for (int i = 0; i < MAX_CONNECTIONS; i++)
		all_connections[i] = -1;
	all_connections[0] = _sockfd;

	while (true){
		FD_ZERO(&_readfd);
		
		for (int i = 0; i < MAX_CONNECTIONS; i++)
			if (all_connections[i] >= 0)
				FD_SET(all_connections[i], &_readfd);
		
		// if ((selectval = select(FD_SETSIZE, &_readfd, NULL, NULL, setTimeval())) < 0){
		if ((selectval = select(FD_SETSIZE, &_readfd, NULL, NULL, NULL)) < 0){				// change SETSIZE for more efficiency
			perror("ERROR on select");
			exit(1);
		}
		else if (selectval == 0){
			printf("TIMEOUT \n");
			exit(1);
		}
		else if (selectval >= 0){		 /* select() woke up. Identify the fd that has events */
			printf("Server-select() is OK...\n");
			if (add_client())
				continue;				//go back to beginning of the loop - don't go to request_handler
		}

		request_handler();				// call only when it's not a connection with a client
	}
}