/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gciPassBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:36:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/14 09:59:48 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg_format/Body.hpp"
#include "msg_format/StatusLine.hpp"
#include "Request.hpp"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <cstring>


// GET : QUERY_STRING + PATH_INFO >> run execve(youpi.exe, coucou.bla, env)
// POST : PATH_INFO + CONTENT_length >> pipe + run execve(youpi.exe, coucou.bla, env) + write post body

#include <sstream>
#include "Cgi.hpp"
int main(void)
{
	Body vide;
	Request req;

	try
	{
		req += "GET /test/ls?dragoon HTTP/1.1\r\nhost:server\r\n\r\n";
		// req += "POST /test/cat HTTP/1.1\r\nhost:server\r\ncontent-length:9\r\n\r\ndragoon\r\n";
		req.parsingCheck();
	}

	// Setting the response with the StatusLine previously sent, and with this request
	// object containing the full request
	catch (const StatusLine& staLine)
	{
		staLine.print();
		req.print();
		
		CGI cgi(&vide, &req);
		try{
			cgi.executeCGI();
		}
		catch (std::exception &e){
			std::cerr << e.what();
		}
	}
	
	return 0;
}