/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationObj.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 15:17:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/03 17:11:35 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationObj.hpp"

// ============================================================================
// =========================== COPLIEN FORM ===================================

Location::Location(ServerInfo *s) : _srv(s) { }

Location::Location(Location const &loc) : _srv(loc._srv), _root(loc._root), 
_upload_store(loc._upload_store), _allow_methd(loc._allow_methd), _index(loc._index)
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

std::string const &Location::getUploadStore() const { return _upload_store; }

std::vector<std::string> const &Location::getMethods() const { return _allow_methd; }

std::vector<std::string> const &Location::getIndex() const { return _index; }

std::vector<std::string> const &Location::getCgiExe() const {return _cgi_exe; }

std::string const &Location::getCgiPath() const {return _cgi_path; }


// ============================================================================
// =============================== SETTERS ====================================

/**
** set variable inside location object
** @param nb is which method of the object is choosen
** @param 
*/
void	Location::setLocation(int nb, int const &pos, std::string const &buf)
{
	typedef void (Location::*MemFuncPtr)(const char*);
	MemFuncPtr F[] = { &Location::setMethods, &Location::setIndex,
                        &Location::setUploadStore, &Location::setRoot, &Location::setCgiExe,
                        &Location::setCgiPath };

    const char *tmp = buf.c_str() + pos;
	int i = 0;

	while (isspace(tmp[i]))
        i++;

	(this->*F[nb])(tmp + i);
}

void Location::setRoot(char const *r) 
{
	std::string cString = r;
	if (numberOfWords(r) != 1)
		throw std::runtime_error("Error : " + std::string(cString) + " - put only one root path\n");
	_root = *wsTrim(cString);
}

void Location::setUploadStore(char const *u) 
{
	std::string cString = u;
	if (numberOfWords(u) != 1)
		throw std::runtime_error("Error : " + std::string(cString) + " - put only one upload_store input\n");
	_upload_store = *wsTrim(cString);
}

void Location::setMethods(char const *n) 
{
	setStringArray(n, _allow_methd);
	const char *method_checking[] = { "POST", "GET", "HEAD", "DELETE", "PUT"};
	for (size_t i = 0; i < _allow_methd.size(); i++){
		for (size_t j = 0; j < 5; j++){
			if (!strcmp(method_checking[j], _allow_methd[i].c_str()))
				break;
			if (j == 4)
				throw std::runtime_error("Error : method " + std::string(_allow_methd[i]) + " is not accepted\n");
		}
	}
}

void Location::setIndex(char const *n) { setStringArray(n, _index); }

void Location::setCgiExe(char const *c) 
{
	setStringArray(c, _cgi_exe);
	if (_cgi_exe.size() != 2)
		throw std::runtime_error("Wrong cgi input in the config file\n"); 
}

void Location::setCgiPath(char const *c) 
{
	std::string cString = c;
	if (numberOfWords(c) != 1)
		throw std::runtime_error("Error : " + std::string(cString) + " - put only one cgi path\n");
	_cgi_path = *wsTrim(cString);
}




// ============================================================================
// =============================== METHODS ====================================

void Location::printLocation(const std::string& locName) const
{
	std::cout << "\nLOCATION\n-------------------------\n"
			<< "root = |" << locName << "|\n"
			<< "root = |" << _root << "|\n"
			<< "upload_store = |" << _upload_store << "|\n"
			<< "cgi_exe = |" << _cgi_exe[0] << " " << _cgi_exe[1] << "|\n"
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