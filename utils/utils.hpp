/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:19:48 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/20 15:39:11 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <vector>

// Converts a char upper case to lower case
char asciiToLower(char in);

// Return a string containing a number (equivalent to atoi)
std::string convertNbToString(size_t nb);

// Return a vector of string containing a line splitted with a sep
std::vector<std::string> splitWithSep(std::string line, char sep);

#endif