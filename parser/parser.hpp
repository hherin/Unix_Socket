/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:30:15 by hherin            #+#    #+#             */
/*   Updated: 2021/04/27 13:35:58 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "ServerInfo.hpp"
# include <string>
# include <fstream>
# include <map>
# include <cctype>  // function isspace
# include <iostream>

int	cleanLineFromSpaces(std::string &buf);
int	bracketRegulator(int &bracket, std::string const &buf);

#endif