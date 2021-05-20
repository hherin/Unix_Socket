/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:19:48 by llefranc          #+#    #+#             */
/*   Updated: 2021/05/20 14:29:52 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
char asciiToLower(char in);
std::string convertNbToString(size_t nb);
std::vector<std::string> stringDelimSplit(std::string const &str, const char *delim);

#endif