/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:19:48 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/25 14:31:57 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

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


#endif