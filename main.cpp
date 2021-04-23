/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:07:48 by hherin            #+#    #+#             */
/*   Updated: 2021/04/23 15:29:15 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "includes/http.hpp"

// int main()
// {
//     http h;
//     h.cliConnect();
//     return 0;
// }

#include "server/ServerSocket.hpp"
#include "server/HttpServer.hpp"
#include "includes/FileParser.hpp"
#include <vector>
#include <list>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Wrong output\n";
        exit(1);
    }
    
    FileParser conf(av[1]);
    
    std::map<int, std::vector<ServerInfo> > m_srv = conf.getConfig();
	// PARTIE PARSEUR

	// boucle pour add tous les sockets >> ou les mettre dans la boucle en dessous ?
    std::vector<int> sockArray;
    for (std::map<int, std::vector<ServerInfo> >::iterator it = m_srv.begin(); it != m_srv.end(); it++)
        sockArray.push_back(it->first);
    
    std::cout << "NB socket " << sockArray.size() << "\n";
	// int sockArray[] = {3490};

	HttpServer server;

	// Creating sockets and binding them to a port
	try
	{
		for (int i = 0; i < 1; ++i)
			server.addAcceptSocket(ServerSocket(sockArray[i], 5));
	}
	catch (const char* msg)
	{
		std::cerr << msg;
		exit(EXIT_FAILURE);
	}
	
	server.etablishConnection();

    return 0;
}

/*

int main()
{
	ServerSocket s1(port, max client);

	s1.create();

	while (true)
	{
		select();
	}
}


*/
