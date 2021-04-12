/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:58:27 by hherin            #+#    #+#             */
/*   Updated: 2021/04/12 18:30:08 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.hpp"

server::server() : _port(-1), _max_clients(5), _autoindex(0)  { }

server::~server() { }

int const &server::getPort() { return _port; }

std::string const &server::getError() { return _error_path; }

std::vector<std::string> const &server::getNames() { return _names; }

#include <iostream>
/**
** set variable inside server object
** param nb is which method of the object is choosen
** param (*D) conversion function to pass in class' method
*/
void	server::setServer(int nb, int const &pos, std::string const &buf)
{
	typedef void (server::*MemFuncPtr)(const char*);
	MemFuncPtr F[] = { &server::setPort, &server::setError, &server::setName };
    const char *tmp = buf.c_str() + pos;
	int i = 0;

	while (isspace(tmp[i]))
        i++;

	(this->*F[nb])(tmp + i);
}

void server::setPort(char const *p) { _port = atoi(p); }

void server::setError(char const *e) { _error_path = e; }

void server::setName(char const *n) 
{
    char *tmp = strdup(n);
    char *token = strtok(tmp, "\t\v\f\r ");

    while (token){
        _names.push_back(token);
        token = strtok(NULL, "\t\v\f\r ");
    }
    delete tmp;
}


