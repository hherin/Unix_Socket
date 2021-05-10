
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:07:48 by hherin            #+#    #+#             */
/*   Updated: 2021/04/27 16:13:39 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/ServerSocket.hpp"
#include "server/HttpServer.hpp"
#include "parser/FileParser.hpp"
#include <vector>
#include <list>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Fatal error: wrong arguments\n";
        exit(EXIT_FAILURE);
    }
    
    FileParser conf(av[1]);
    
    std::map<int, std::vector<ServerInfo> > m_srv = conf.getConfigFile();
	// PARTIE PARSEUR

	// boucle pour add tous les sockets >> ou les mettre dans la boucle en dessous ?
    std::vector<int> sockArray;
    for (std::map<int, std::vector<ServerInfo> >::iterator it = m_srv.begin(); it != m_srv.end(); it++)
        sockArray.push_back(it->first);

	HttpServer server;

	// Creating sockets and binding them to a port
	try
	{
		for (size_t i = 0; i < sockArray.size(); ++i)
			server.addServerSocket(ServerSocket(sockArray[i], 5));
			
		server.etablishConnection(m_srv);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
		exit(EXIT_FAILURE);
	}

    return 0;
}
