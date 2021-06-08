/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gciPassBody.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:36:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/08 17:26:23 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msg_format/Body.hpp"
#include <iostream>
#include <unistd.h>
#include <fstream>

// std::string cgiexecPassBody(Body *body, RequestLine *req, char **env)
// {
// 	std::string msgbody;
// 	std::streambuf *redirect, *backup;
// 	std::ifstream output;
// 	std::pair<std::string, std::string> path;
		
// 	backup = std::cout.rdbuf();
// 	redirect = output.rdbuf();
// 	std::cout.rdbuf(redirect);
// 	pid_t pid = fork();

	
// 	if (!pid){
// 		path.first = req->getPath();
// 		if (execve("./exec.cgi", NULL, NULL) < 0)
// 			throw "Error with execve occurs\n";
// 	}
// 	else if (pid > 0){
// 		output >> msgbody;
// 		std::cout.rdbuf(backup);
// 		output.close();
// 	}
// 	else{
// 		output.close(); 
// 		throw "Error in fork occurs\n";}
	
// 	return msgbody;
// }

// first part contain the path to the file, second part name of file
std::pair<std::string, std::string> *SplitPathForExec(std::string path)
{
	std::pair<std::string, std::string> pathAndFile;
	
	pathAndFile.first = path;
	pathAndFile.second = "." + path.c_str() + path.find_last_of("/");
	pathAndFile.second += 
	return &pathAndFile;
}

int main(void)
{
	std::string str = "hello/coco/bono";

	std::cout << SplitPathForExec(str)->first << "\n";

	return 0;
}