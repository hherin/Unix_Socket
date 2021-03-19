/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:39:35 by hherin            #+#    #+#             */
/*   Updated: 2021/03/19 16:16:56 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>

#include <unistd.h>
#include <string.h>

#include <sys/types.h> /* Voir NOTES */ 
#include <sys/socket.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "socket.hpp"

int main(void) {
   int sockfd, newsockfd, portno;
   unsigned int clilen, servlen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   /* GET HOST NAME */
   char *hostname = (char*)malloc(sizeof(char) * 2);
   int hostsize = 100;
   if (gethostname(hostname, hostsize) < 0)
   {
      perror("ERROR on gethostname");
      exit(1);
   }
   printf("HSOT Name %s\n", hostname);

   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 3490;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);

   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   // fcntl(sockfd, F_SETFL, O_NONBLOCK);
    servlen = sizeof(serv_addr);
   if (getsockname(sockfd,(struct sockaddr *) &serv_addr,&servlen)
         == -1) {
      perror("getting socket name");
      exit(1);
   }

   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   // printf("HOSTE NAME %s\n", getsockname())
   /* Accept actual connection from the client */
   newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
	
   if (newsockfd < 0) {
      perror("ERROR on accept");
      exit(1);
   }
   /* If connection is established then start communicating */
   bzero(buffer,256);
   n = read( newsockfd,buffer,255 );
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }

   printf("Here is the message: %s\n",buffer);
   
   /* Write a response to the client */
   n = write(newsockfd,"I got your message",18);
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }

   return 0;
}