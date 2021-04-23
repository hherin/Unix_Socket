/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInfo.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:58:27 by hherin            #+#    #+#             */
/*   Updated: 2021/04/23 15:48:08 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerInfo.hpp"

ServerInfo::ServerInfo() : _max_clients(5), _autoindex(0)  { }

ServerInfo::~ServerInfo() { }

int const &ServerInfo::getMaxClientsBS() { return _max_clients; }

bool const &ServerInfo::getAutoIndex() { return _autoindex; }

std::string const &ServerInfo::getError() { return _error_path; }

std::string const &ServerInfo::getRoot() { return _root; }

std::string const &ServerInfo::getAuthBasic() { return _auth_basic; }

std::string const &ServerInfo::getAuthBasicFile() { return _auth_b_usr_file; }

std::string const &ServerInfo::getUploadStore() { return _upload_store; }

std::vector<std::string> const &ServerInfo::getNames() { return _names; }

std::vector<std::string> const &ServerInfo::getMethods() { return _allow_methd; }

std::vector<std::string> const &ServerInfo::getIndex() { return _index; }

std::vector<int> const &ServerInfo::getPort() { return _port; }

std::vector<ServerInfo> const &ServerInfo::getLocation() { return _location; }

/**
** set variable inside server object
** param nb is which method of the object is choosen
** param (*D) conversion function to pass in class' method
*/
void	ServerInfo::setServer(int nb, int const &pos, std::string const &buf)
{
	typedef void (ServerInfo::*MemFuncPtr)(const char*);
	MemFuncPtr F[] = { &ServerInfo::setPort, &ServerInfo::setError, &ServerInfo::setNames, &ServerInfo::setMethods, &ServerInfo::setIndex,
                        &ServerInfo::setAuthBasic, &ServerInfo::setAuthBasicFile, &ServerInfo::setMaxClientsBS, &ServerInfo::setAutoIndex,
                        &ServerInfo::setUploadStore, &ServerInfo::setRoot };
                        
    const char *tmp = buf.c_str() + pos;
	int i = 0;

	while (isspace(tmp[i]))
        i++;

    
	(this->*F[nb])(tmp + i);
}

void ServerInfo::setLocation(ServerInfo &l) { _location.push_back(l); }

void ServerInfo::setMaxClientsBS(char const *m) { _max_clients = atoi(m); }

void ServerInfo::setAutoIndex(char const *i) { _autoindex = (!strncmp("on", i, 3)) ? 1 : 0; }

void ServerInfo::setError(char const *e) { _error_path = e; }

void ServerInfo::setRoot(char const *r) { _root = r; }

void ServerInfo::setAuthBasic(char const *a) { _auth_basic = a; }

void ServerInfo::setAuthBasicFile(char const *f) { _auth_b_usr_file = f; }

void ServerInfo::setUploadStore(char const *u) { _upload_store = u; }

void ServerInfo::setNames(char const *n) { setStringArray(n, _names); }

void ServerInfo::setMethods(char const *n) { setStringArray(n, _allow_methd); }

void ServerInfo::setIndex(char const *n) { setStringArray(n, _index); }

void ServerInfo::setPort(char const *p) 
{
    char *tmp = strdup(p);
    char *token = strtok(tmp, "\t\v\f\r ");

    while (token){
        _port.push_back(atoi(token));
        token = strtok(NULL, "\t\v\f\r ");
    }
    delete tmp; 
}

void ServerInfo::setStringArray(char const *n, std::vector<std::string> &v) 
{
    char *tmp = strdup(n);
    char *token = strtok(tmp, "\t\v\f\r ");

    while (token){
        v.push_back(token);
        token = strtok(NULL, "\t\v\f\r ");
    }
    delete tmp;
}


