/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:29:16 by hherin            #+#    #+#             */
/*   Updated: 2021/04/27 13:30:58 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

int	cleanLineFromSpaces(std::string &buf)
{
	int i = 0;
	while (isspace(buf[i]))
		buf.erase(0, 1);

	if (buf.size()){
		i = buf.size() - 1;
		while (isspace(buf[i]))
			buf.erase(i, 1);
	}
	return 0;
}

int	bracketRegulator(int &bracket, std::string const &buf)
{
	size_t pos = -1; 
	while ( (pos = buf.find_first_of('{', pos + 1)) != std::string::npos) 
		bracket++;
	
	pos = -1;
	while ( (pos = buf.find_first_of('}', pos + 1)) != std::string::npos)
		bracket--;
	return 1;
}