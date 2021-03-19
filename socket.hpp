/* ************************************************************************** */
/*	                                                                         */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:20:33 by hherin            #+#    #+#             */
/*   Updated: 2021/03/17 14:34:28 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

// #include <sys/socket.h> 
#include <netinet/in.h> 

struct megaHost
{
    struct sockaddr_in  addrHost;
    struct hostent      *hostInfo;
};

#endif