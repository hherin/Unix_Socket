/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:53:45 by hherin            #+#    #+#             */
/*   Updated: 2021/06/14 10:14:56 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"


/* =============================================================================
 =============================== COPLIEN FORM ================================*/


// ADD FILE AS PARAMETERS IF .bla
CGI::CGI(Body *body, Request *req, const std::string &realUri, const std::string& exec) 
			: _envvar(NULL), _emptyBody(body), _req(req), _exec_extension(exec), _realUri(realUri)
{	
	std::string tmpBuf;
	
	_path_info = *SplitPathForExec(_realUri);
	
	// set environment variable for the CGI
	_envvar = new char*[3];
	_envvar[0] = strdup(("PATH_INFO=" + _path_info.first).c_str());
	if (_req->getMethod() == GET){
		tmpBuf = "QUERY_STRING=" + _req->getQuery();
		_envvar[1] = strdup(tmpBuf.c_str());
	}
	else {
		std::stringstream intToString;
		intToString << _req->getBody().getBody().size();
		tmpBuf = std::string("CONTENT_LENGTH=") + intToString.str();
		_envvar[1] = strdup(tmpBuf.c_str());
		std::cerr << "LENGTH BODY " << _envvar[1] << "\n";
		std::cerr << "BODY ." << _req->getBody().getBody() << ".\n";
	}
	_envvar[2] = NULL;

	int nbAlloc = (!_exec_extension.compare(".cgi")) ? 2 : 3;

	_args = new char*[nbAlloc--];
	_args[nbAlloc--] = NULL;
	_args[nbAlloc--] = (!_exec_extension.compare(".cgi")) ? strdup(_path_info.second.c_str()) : 
															strdup(_exec_extension.c_str());
	(!nbAlloc) ? _args[0] = strdup(_path_info.second.c_str()) : 0;

}

CGI::CGI(CGI const &copy) : _emptyBody(copy._emptyBody), _req(copy._req),
							 _exec_extension(copy._exec_extension), _realUri(copy._realUri),
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
	int fdPipe[2];
	int fdPost[2];
	
	if (pipe(fdPipe) < 0 || (_req->getMethod() == POST && pipe(fdPost) < 0))
		throw std::runtime_error("Error with pipe\n");
	pid_t pid = fork();
	
	if (!pid){
		std::cout << "CHild process \n";
		dup2(fdPipe[1], STDOUT_FILENO);
		close(fdPipe[0]);
		close(fdPipe[1]);
		
		if (_req->getMethod() == POST){
			dup2(fdPost[0], STDIN_FILENO);
			close(fdPost[0]);
			close(fdPost[1]);
		}
		// char tmp[10];
		// read(0, tmp, 9);
		// std::cerr << "write received :." << tmp << ".\n";
		// The path and name of executable are separate in a pair
		std::pair<std::string, std::string> path = *SplitPathForExec(_req->getPath());

		chdir(_path_info.first.c_str());

		if (execve(_path_info.second.c_str(), _args, _envvar) < 0){
			std::cerr << "Error with execve from cgi\n";
			exit(1);
		}
	
	}
	else if (pid > 0){
		std::cerr << "Parent process\n";
int nb;
		if (_req->getMethod() == POST){
			if ((nb = write(fdPost[1], _req->getBody().getBody().c_str(), _req->getBody().getBody().size())) < 0)
				throw std::runtime_error("ERROR with write in cgi\n");
			std::cerr << "REturn of write " << nb << "\n";
			close(fdPost[0]);
			close(fdPost[1]);
		}
		// waitpid(pid, NULL, 0);
		close(fdPipe[1]);
		char buf[2046];
		std::string msgbody;
		
		std::cerr << "before reading\n";

		
		while (read(fdPipe[0], buf, 2046) == 2046)
			msgbody += buf;
		msgbody += buf;
		
		close(fdPipe[0]);
		// close(fdPipe[0]);
		std::cerr << "fdPipe now closed\n";

		_emptyBody->setBuff(msgbody);
		// 
		_emptyBody->setSize(msgbody.size() - msgbody.find_first_of("\r\n\r\n") - 2); 
	}
	else{
		close(fdPipe[1]); close(fdPipe[0]);
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