/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:53:45 by hherin            #+#    #+#             */
/*   Updated: 2021/06/11 14:35:25 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"

// https://jkorpela.fi/forms/cgic.html

/* =============================================================================
 =============================== COPLIEN FORM ================================*/


// ADD FILE AS PARAMETERS IF .bla
CGI::CGI(Body *body, Request *req, const std::string& exec) 
			: _envvar(NULL), _requestBody(body), _req(req), _exec_extension(exec)
{
	std::string tmpBuf;
	
	_path_info = *SplitPathForExec(req->getPath());
	
	// set environment variable for the CGI
	_envvar = new char*[3];
	_envvar[0] = strdup(("PATH_INFO=" + _path_info.second).c_str());
	if (_req->getMethod() == GET){
		tmpBuf = "QUERY_STRING=" + _req->getQuery();
		_envvar[1] = strdup(tmpBuf.c_str());
	}
	else {
		std::stringstream intToString;
		intToString << _req->getBody().getSize();
		tmpBuf = std::string("CONTENT_LENGHT=") + intToString.str();
		_envvar[1] = strdup(tmpBuf.c_str());
	}
	_envvar[2] = NULL;
}

CGI::CGI(CGI const &copy) : _requestBody(copy._requestBody), _req(copy._req),
							 _exec_extension(copy._exec_extension),
							_path_info(copy._path_info)
{
	_envvar = new char*[2];
	_envvar[0] = strdup(copy._envvar[0]);
	_envvar[1] = strdup(copy._envvar[1]);
}

CGI &CGI::operator=(CGI &copy)
{
	CGI tmp(*this);
	mySwap(tmp, copy);
	return *this;
}

CGI::~CGI()
{
	delete _envvar[0]; _envvar[0] = NULL;
	delete _envvar[1]; _envvar[1] = NULL;
	delete[] _envvar;
}

/* =============================================================================
 =============================== PUBLIC METHODS ===============================*/

void CGI::executeCGI()
{
	std::streambuf *redirectOut, *backupOut, *redirectIn, *backupIn;
	std::ifstream output;
	std::ofstream input;
	int post_fd[2];
	
	// If the method is POST cin is redirect
	if (_req->getMethod() == POST){
		backupIn = std::cin.rdbuf();
		redirectIn = input.rdbuf();
		std::cin.rdbuf(redirectIn);
	}
	
	// save std::cout stream into backup then redirect output fd into std::cout
	backupOut = std::cout.rdbuf();
	redirectOut = output.rdbuf();
	std::cout.rdbuf(redirectOut);
	
	pid_t pid = fork();
	
	if (!pid){
		output.close();
		
		if (_req->getMethod() == POST)
			input << _requestBody->getBody();
		// input.close();
			
		// The path and name of executable are separate in a pair
		std::pair<std::string, std::string> path = *SplitPathForExec(_req->getPath());

		chdir(_path_info.first.c_str());
		if (execve(_path_info.second.c_str(), NULL, _envvar) < 0){
			std::cerr << "Error with execve from cgi\n";
			exit(1);
	
		// extract output from execve into msgbody, finally set the body object
		std::string msgbody;
		output >> msgbody;
		output.close();

		_requestBody->setBuff(msgbody);
			
		// retrieve std::cout fd and close the temporary stream
		std::cout.rdbuf(backupOut);
		if (_req->getMethod() == POST)
			std::cin.rdbuf(backupIn);
		}
	}
	else if (pid > 0){
		input.close();
		if (_req->getMethod() == POST && 
			write(post_fd[1], _requestBody->getBody().c_str(), atoi(_envvar[1])) < 0){
				std::cerr << "Error with write in CGI\n";
			}
	}
	else{
		output.close(); 
		input.close();
		throw std::runtime_error("Error in fork occurs\n");
	}
}


/* =============================================================================
 =============================== PRIVATE METHODS ===============================*/
 
void CGI::mySwap(CGI &a, CGI &b)
{
	std::swap(a._envvar, b._envvar);
	std::swap(a._requestBody, b._requestBody);
	std::swap(a._req, b._req);
	std::swap(a._exec_extension, b._exec_extension);
	std::swap(a._path_info, b._path_info);
}