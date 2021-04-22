/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:07:48 by hherin            #+#    #+#             */
/*   Updated: 2021/04/21 16:09:29 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "includes/http.hpp"

// int main()
// {
//     http h;
//     h.cliConnect();
//     return 0;
// }

#include "server/Socket.hpp"
#include "server/HttpServer.hpp"

#include <vector>
#include <list>

int main()
{

	// PARTIE PARSEUR

	// boucle pour add tous les sockets >> ou les mettre dans la boucle en dessous ?
	int sockArray[] = {3490};

	HttpServer server;

	// Creating sockets and binding them to a port
	try
	{
		for (int i = 0; i < 1; ++i)
			server.addAcceptSocket(Socket(sockArray[i], 5));
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
	Socket s1(port, max client);

	s1.create();

	while (true)
	{
		select();
	}
}


*/
