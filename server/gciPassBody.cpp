/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gciPassBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:36:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/11 14:32:27 by heleneherin      ###   ########.fr       */
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
// POST : PATH_INFO + CONTENT_LENGHT >> pipe + run execve(youpi.exe, coucou.bla, env) + write post body

#include <sstream>
#include "cgi.hpp"
int main(void)
{
	Body vide;
	Request req;

	try
	{
		// req += "GET /test/exec.cgi?dragoon HTTP/1.1\r\nhost:server\r\n\r\n";
		req += "POST /test/cat HTTP/1.1\r\nhost:server\r\ncontent-lenght:9\r\n\r\ndragoon\r\n";
		req.parsingCheck();
	}

	// Setting the response with the StatusLine previously sent, and with this request
	// object containing the full request
	catch (const StatusLine& staLine)
	{
		staLine.print();
		req.print();
		
		CGI cgi(&vide, &req);
		cgi.executeCGI();
		// try{
		// 	cgiexecPassBody(&vide, &req);
		// }
		// catch (const char *e){
		// 	std::cerr << e;
		// }
	}
	
	return 0;
}