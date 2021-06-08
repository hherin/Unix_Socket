/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gciPassBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:36:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/03 13:55:49 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg_format/Body.hpp"
#include <iostream>
#include <unistd.h>
#include <fstream>

std::string cgiPassBody(Body *body, std::string *uri)
{
    std::string msgbody;
	std::streambuf *redirect, *backup;
	std::ifstream output;
		
	backup = std::cout.rdbuf();
	redirect = output.rdbuf();
	std::cout.rdbuf(redirect);
	pid_t pid = fork();

	if (!pid){
		if (execve("./exec.cgi", NULL, NULL) < 0)
			throw "Error with execve occur\n";
	}
	else if (pid > 0){
		output >> msgbody;
		std::cout.rdbuf(backup);
        output.close();
	}
	else
		throw "Error in fork occur\n";
    
	return msgbody;
}