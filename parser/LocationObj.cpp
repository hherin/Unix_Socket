/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationObj.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:17:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/03 17:33:47 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationObj.hpp"

// ============================================================================
// =========================== COPLIEN FORM ===================================

Location::Location(ServerInfo *s) : _srv(s), _autoindex(0) { }

Location::Location(Location const &loc) : _srv(loc._srv), _root(loc._root), 
_auth_basic(loc._auth_basic), _auth_b_usr_file(loc._auth_b_usr_file), 
_upload_store(loc._upload_store), _allow_methd(loc._allow_methd), _index(loc._index),
_autoindex(loc._autoindex)
{}

Location &Location::operator=(Location const &loc)
{
    Location tmp(loc);
    myswap(tmp, *this);
    return *this;
}

Location::~Location() { }

// ============================================================================
// =============================== GETTERS ====================================

std::string const &Location::getRoot() const { return _root; }

std::string const &Location::getAuthBasic() const { return _auth_basic; }

std::string const &Location::getAuthBasicFile() const { return _auth_b_usr_file; }

std::string const &Location::getUploadStore() const { return _upload_store; }

std::vector<std::string> const &Location::getMethods() const { return _allow_methd; }

std::vector<std::string> const &Location::getIndex() const { return _index; }

std::string const &Location::getCgiExe() const {return _cgi_exe; }

std::string const &Location::getCgiPath() const {return _cgi_path; }

bool const &Location::getAutoIndex() const { return _autoindex; }


// ============================================================================
// =============================== SETTERS ====================================

/**
** set variable inside location object
** param nb is which method of the object is choosen
** param (*D) conversion function to pass in class' method
*/
void	Location::setLocation(int nb, int const &pos, std::string const &buf)
{
	typedef void (Location::*MemFuncPtr)(const char*);
	MemFuncPtr F[] = { &Location::setMethods, &Location::setIndex, &Location::setAuthBasic, 
                        &Location::setAuthBasicFile, &Location::setAutoIndex, 
                        &Location::setUploadStore, &Location::setRoot, &Location::setCgiExe,
                        &Location::setCgiPath };

    const char *tmp = buf.c_str() + pos;
	int i = 0;

	while (isspace(tmp[i]))
        i++;

	(this->*F[nb])(tmp + i);
}

void Location::setRoot(char const *r) { _root = r; }

void Location::setAuthBasic(char const *a) { _auth_basic = a; }

void Location::setAuthBasicFile(char const *f) { _auth_b_usr_file = f; }

void Location::setUploadStore(char const *u) { _upload_store = u; }

void Location::setMethods(char const *n) { setStringArray(n, _allow_methd); }

void Location::setIndex(char const *n) { setStringArray(n, _index); }

void Location::setCgiExe(char const *c) { _cgi_exe = c; }

void Location::setCgiPath(char const *c) { _cgi_path = c; }

void Location::setAutoIndex(char const *i) { _autoindex = (!strncmp("on", i, 3)) ? 1 : 0; }


// ============================================================================
// =============================== METHODS ====================================

void Location::printLocation(const std::string& locName) const
{
	std::cout << "\nLOCATION\n-------------------------\n"
			<< "name = |" << locName << "|\n"
			<< "root = |" << _root << "|\n"
			<< "auth_basic = |" << _auth_basic << "|\n"
			<< "auth_b_usr_file = |" << _auth_b_usr_file << "|\n"
			<< "upload_store = |" << _upload_store << "|\n"
			<< "cgi_exe = |" << _cgi_exe << "|\n"
			<< "cgi_path = |" << _cgi_path << "|\n"
			<< "autoindex = |" << _root << "|\n";
	
	for (std::vector<std::string>::const_iterator it = _allow_methd.begin(); it != _allow_methd.end(); ++it)
		std::cout << "method = |" << *it << "|\n";

	for (std::vector<std::string>::const_iterator it = _index.begin(); it != _index.end(); ++it)
		std::cout << "index = |" << *it << "|\n";
	
	std::cout << "-------------------------\n\n";
}


// ============================================================================
// ========================== PRIVATE METHODS =================================
template <class T>
void Location::myswap(T t1, T t2)
{
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}