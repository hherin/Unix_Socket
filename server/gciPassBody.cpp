/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gciPassBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:36:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/09 18:03:49 by hherin           ###   ########.fr       */
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

void cgiexecPassBody(Body *body, Request *req, const std::string& exec = "")
{
	std::streambuf *redirect, *backup;
	std::ifstream input;
(void)exec;
	// save std::cout stream into backup then redirect input fd into std::cout
	backup = std::cout.rdbuf();
	redirect = input.rdbuf();
	std::cout.rdbuf(redirect);
	
	pid_t pid = fork();
	if (!pid){
		// The path and name of executable are separate in a pair
		std::pair<std::string, std::string> path = *SplitPathForExec(req->getPath());

		chdir(path.first.c_str());

		if (execve(path.second.c_str(), NULL, NULL) < 0){
			std::cerr << "Error with execve from cgi\n";
			exit(1);
		}
		
	}
	else if (pid > 0){
		// write input from execve into msgbody, finally set the body object
		std::string msgbody;
		input >> msgbody;

		body->setBuff(msgbody);
		
		// retrieve std::cout fd and close the temporary stream
		std::cout.rdbuf(backup);
		input.close();
	}
	else{
		input.close(); 
		throw std::runtime_error("Error in fork occurs\n");
	}
}



#include <sstream>
#include "cgi.hpp"
int main(void)
{
	Body vide;
	Request req;

	try
	{
		req += "GET /test/exec.cgi?dragoon HTTP/1.1\r\nhost:server\r\n\r\n";
		// req += "POST /test/CGItest/exec.cgi HTTP/1.1\r\nhost:server\r\ncontent-lenght:9\r\n\r\ndragoon\r\n";
		req.parsingCheck();
	}

	// Setting the response with the StatusLine previously sent, and with this request
	// object containing the full request
	catch (const StatusLine& staLine)
	{
		staLine.print();
		req.print();
		
		CGI(&vide, &req);
		
		// try{
		// 	cgiexecPassBody(&vide, &req);
		// }
		// catch (const char *e){
		// 	std::cerr << e;
		// }
	}
	
	return 0;
}