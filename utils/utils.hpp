/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:19:48 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/25 15:43:00 by hherin           ###   ########.fr       */
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

// srv = list of virtual server for one port, names.first = name of virtual server, names.second = location name
Location *locationSearcher(std::vector<ServerInfo> *srv, std::pair<std::string, std::string> const &names);

// Remove whitespaces of given buffer and return its pointer
std::string *wsTrim(std::string &buf);

#endif