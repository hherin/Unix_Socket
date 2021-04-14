/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:58:27 by hherin            #+#    #+#             */
/*   Updated: 2021/04/14 14:02:52 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

server::server() : _max_clients(5), _autoindex(0)  { }

server::~server() { }

int const &server::getMaxClientsBS() { return _max_clients; }

bool const &server::getAutoIndex() { return _autoindex; }

std::string const &server::getError() { return _error_path; }

std::string const &server::getRoot() { return _root; }

std::string const &server::getAuthBasic() { return _auth_basic; }

std::string const &server::getAuthBasicFile() { return _auth_b_usr_file; }

std::string const &server::getUploadStore() { return _upload_store; }

std::vector<std::string> const &server::getNames() { return _names; }

std::vector<std::string> const &server::getMethods() { return _allow_methd; }

std::vector<std::string> const &server::getIndex() { return _index; }

std::vector<int> const &server::getPort() { return _port; }

std::vector<server> const &server::getLocation() { return _location; }

/**
** set variable inside server object
** param nb is which method of the object is choosen
** param (*D) conversion function to pass in class' method
*/
void	server::setServer(int nb, int const &pos, std::string const &buf)
{
	typedef void (server::*MemFuncPtr)(const char*);
	MemFuncPtr F[] = { &server::setPort, &server::setError, &server::setNames, &server::setMethods, &server::setIndex,
                        &server::setAuthBasic, &server::setAuthBasicFile, &server::setMaxClientsBS, &server::setAutoIndex,
                        &server::setUploadStore, &server::setRoot };
                        
    const char *tmp = buf.c_str() + pos;
	int i = 0;

	while (isspace(tmp[i]))
        i++;

    
	(this->*F[nb])(tmp + i);
}

void server::setLocation(server &l)
{
    _location.push_back(l);
}

void server::setMaxClientsBS(char const *m) { _max_clients = atoi(m); }

void server::setAutoIndex(char const *i) { _autoindex = (!strncmp("on", i, 3)) ? 1 : 0; }

void server::setError(char const *e) { _error_path = e; }

void server::setRoot(char const *r) { _root = r; }

void server::setAuthBasic(char const *a) { _auth_basic = a; }

void server::setAuthBasicFile(char const *f) { _auth_b_usr_file = f; }

void server::setUploadStore(char const *u) { _upload_store = u; }

void server::setNames(char const *n) { setStringArray(n, _names); }

void server::setMethods(char const *n) { setStringArray(n, _allow_methd); }

void server::setIndex(char const *n) { setStringArray(n, _index); }

void server::setPort(char const *p) 
{
    char *tmp = strdup(p);
    char *token = strtok(tmp, "\t\v\f\r ");

    while (token){
        _port.push_back(atoi(token));
        token = strtok(NULL, "\t\v\f\r ");
    }
    delete tmp; 
}

void server::setStringArray(char const *n, std::vector<std::string> &v) 
{
    char *tmp = strdup(n);
    char *token = strtok(tmp, "\t\v\f\r ");

    while (token){
        v.push_back(token);
        token = strtok(NULL, "\t\v\f\r ");
    }
    delete tmp;
}


