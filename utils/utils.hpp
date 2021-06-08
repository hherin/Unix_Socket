/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:19:48 by llefranc          #+#    #+#             */
/*   Updated: 2021/06/08 16:44:07 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

# include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
# include "../parser/LocationObj.hpp"

class Location; 
class ServerInfo;

// Converts a char upper case to lower case
char asciiToLower(char in);

// Return a string containing a number (equivalent to atoi)
std::string convertNbToString(size_t nb);

// Return a vector of string containing a line splitted with a sep (sep included)
std::vector<std::string> stringDelimSplit(std::string const &str, const char *delim);

// Return a vector of string containing a line splitted with a sep
std::vector<std::string> splitWithSep(std::string line, char sep);

// Push each word of n in the vector v
void setStringArray(char const *n, std::vector<std::string> &v);

// Search inside a map of location names /location block the best possible match with locName. Return NULL
// if no match
std::pair<const std::string, const Location*> 
		matchLocation(std::map<std::string, Location> *loc, const std::string& locName);

// srv = list of virtual server for one port, names.first = name of virtual server, names.second = location name
// Return the best possible location block for a specific host+URI. Return NULL if no match
std::pair<const std::string, const Location*>
		locationSearcher(std::vector<ServerInfo> *srv, std::pair<std::string, std::string> const &names);

// Remove whitespaces of given buffer and return its pointer
std::string *wsTrim(std::string &buf);

// Prints the time of the day and the msg on std::cout
void printLog(const std::string &msg, const std::string& addInfo = "");

// Returns a pointer to the virtual server block that matches hostValue from host header field. 
// If no match, returns NULL.
ServerInfo* findVirtServ(std::vector<ServerInfo>* infoVirServs, const std::string& hostValue);

#endif