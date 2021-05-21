/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:56:49 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/21 15:25:34 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

char asciiToLower(char in)
{
    if (in >= 'A' && in <= 'Z')
        return in + ('a' - 'A');
    return in;
}

std::string convertNbToString(size_t nb)
{
	std::ostringstream oss;
	
	oss << nb;
	return oss.str();
}

std::vector<std::string> stringDelimSplit(std::string const &str, const char *delim)
{
    static std::vector<std::string> strArray;       // use static to return the vector
    size_t posinit = 0, posfind = 0;
    
    strArray.clear();
    while (posfind < str.size()){
        posfind = str.find(delim, posinit + 1);
        
        if (posfind != std::string::npos){
            strArray.push_back(str.substr(posinit, posfind - posinit));
            posinit = posfind;
        }
        else{
            strArray.push_back(str.substr(posinit, str.size() - posinit));
            posfind = str.size();
        }
    }
    return strArray;
}
std::vector<std::string> splitWithSep(std::string line, char sep)
{
	std::vector<std::string> res;
	std::istringstream s(line);

	while (std::getline(s, line, sep))
		res.push_back(line);
	
	return res;
}

void setStringArray(char const *n, std::vector<std::string> &v) 
{
    char *tmp = strdup(n);
    char *token = strtok(tmp, "\t\v\f\r ");

    while (token){
        v.push_back(token);
        token = strtok(NULL, "\t\v\f\r ");
    }
    delete tmp;
}