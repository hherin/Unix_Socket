/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:53:45 by hherin            #+#    #+#             */
/*   Updated: 2021/06/14 19:26:43 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"

/* =============================================================================
 =============================== COPLIEN FORM ================================*/

CGI::CGI(Body *body, Request *req, const std::string &realUri, const std::string& exec) 
			: _envvar(NULL), _emptyBody(body), _req(req), _exec_extension(exec), _realUri(realUri)
{	
	std::string tmpBuf;
	
	_path_info = *SplitPathForExec(_realUri);
	
	// ** set environment variable for the CGI **
	// GET : QUERY_STRING + PATH_INFO 
	// POST : PATH_INFO + CONTENT_length 
	if ((_envvar = new char*[4]) == NULL)
		throw std::runtime_error("Error on a cgi malloc\n");
	_envvar[0] = strdup(("PATH_INFO=" + _realUri).c_str());
	if (_req->getMethod() == GET){
		tmpBuf = "QUERY_STRING=" + _req->getQuery();
		_envvar[1] = strdup(tmpBuf.c_str());
		_envvar[2] = strdup("REQUESTED_METHOD=GET");
	}
	else {
		std::stringstream intToString;
		intToString << _req->getBody().getBody().size();
		tmpBuf = std::string("CONTENT_LENGTH=") + intToString.str();
		_envvar[1] = strdup(tmpBuf.c_str());
		_envvar[2] = strdup("REQUESTED_METHOD=POST");
	}
	_envvar[3] = NULL;

	// ** Set args for execve **
	// if run process for cgi -> only executable as argument
	// else -> _exec_extension is a parameter file for executable _path_info.second
	int nbAlloc = (!_exec_extension.compare(".cgi")) ? 2 : 3;	
	if ((_args = new char*[nbAlloc--]) == NULL)
		throw std::runtime_error("Error on a cgi malloc\n");
	_args[nbAlloc--] = NULL;
	_args[nbAlloc--] = strdup(_path_info.second.c_str());
	(!nbAlloc) ? _args[0] = strdup(_exec_extension.c_str()) : 0;
	std::cerr << "ARGSSSSS " <<  _args[0] << "\n";
	(_exec_extension.compare(".cgi")) ? _openArgfile.open(_realUri) : _openArgfile.close();
}

CGI::CGI(CGI const &copy) : _emptyBody(copy._emptyBody), _req(copy._req),
							_exec_extension(copy._exec_extension), _realUri(copy._realUri),
							_path_info(copy._path_info)
{
	_envvar = new char*[2];
	_envvar[0] = strdup(copy._envvar[0]);
	_envvar[1] = strdup(copy._envvar[1]);

	int nb = 0;
	while (copy._args[nb++]);
	_args = new char*[nb];
	while (--nb > - 1)
		copy._args[nb] = _args[nb];
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

	int i = 0;
	while (_args[i++]){
		delete _args[i]; _args[i] = NULL;}
	delete[] _args;
}


/* =============================================================================
 =============================== PUBLIC METHODS ===============================*/
void CGI::executeCGI()
{
	int fdOut[2];
	int fdIN[2];
	
	if (pipe(fdOut) < 0 || pipe(fdIN) < 0)
		throw std::runtime_error("Error with pipe\n");
	
	pid_t pid = fork();
	
	if (!pid){
		
		// stdout is now a copy of fdOut[1] and in case post method, stdin is a copy of fdIn[0]
		dup2(fdOut[1], STDOUT_FILENO);
		close(fdOut[0]);
		close(fdOut[1]);
		

		dup2(fdIN[0], STDIN_FILENO);
		close(fdIN[0]);
		close(fdIN[1]);

		// change the repo into where the program is
		chdir(_path_info.first.c_str());
		
		std::cerr << "path " << _path_info.second << ".\n";
		int i = -1;
		std::cerr << "ARGS : ";
		while (_args[++i])
			std::cerr << _args[i] << " | ";

		i = 0;
		std::cerr << "\nENVVAR : ";
		while (_envvar[++i])
			std::cerr << _envvar[i] << " | ";
		if (execve(_path_info.second.c_str(), _args, _envvar) < 0){
			std::cerr << "Error with execve from cgi\n";
			exit(1);
		}
	
	}
	else if (pid > 0){
		
		close(fdOut[1]);
		if (_req->getMethod() == POST){
			if (write(fdIN[1], _req->getBody().getBody().c_str(), _req->getBody().getBody().size()) < 0)
				throw std::runtime_error("ERROR with write in cgi\n");
		}
		else{
			std::string tmpBuf;
			_openArgfile >> tmpBuf;
			if (write(fdIN[1], tmpBuf.c_str(), tmpBuf.size()) < 0)
				throw std::runtime_error("ERROR with write in cgi\n");
		}
		close(fdIN[1]);
		close(fdIN[0]);
		
		char buf[2046];
		std::string msgbody;	
		while (read(fdOut[0], buf, 2046) == 2046)
			msgbody += buf;
		msgbody += buf;
		
		close(fdOut[0]);

		_emptyBody->setBuff(msgbody);
		// remove the header part of the cgi output
		_emptyBody->setSize(msgbody.size() - msgbody.find_first_of("\r\n\r\n") - 2); 
	}
	else{
		close(fdOut[1]); close(fdOut[0]);
		if (_req->getMethod() == POST) { close(fdIN[0]); close(fdIN[1]); }
		throw std::runtime_error("Error in fork occurs\n");
	}
}

/* =============================================================================
 =============================== PRIVATE METHODS ===============================*/
 
void CGI::mySwap(CGI &a, CGI &b)
{
	std::swap(a._envvar, b._envvar);
	std::swap(a._emptyBody, b._emptyBody);
	std::swap(a._req, b._req);
	std::swap(a._exec_extension, b._exec_extension);
	std::swap(a._path_info, b._path_info);
}