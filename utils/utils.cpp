/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:56:49 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/05/26 19:06:58 by llefranc         ###   ########.fr       */
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

// srv = list of virtual server for one port, names.first = name of virtual server, names.second = location name
Location *locationSearcher(std::vector<ServerInfo> *srv, std::pair<std::string, std::string> const &names)
{
	for (size_t i = 0; i < srv->size(); i++){													// loop for each virtual server
	
		std::vector<std::string> sinfoNames = (*srv)[i].getNames();

		
        for (size_t j = 0; j < sinfoNames.size(); j++) {                                         // loop for each names in server

			std::cerr << "server name = " << sinfoNames[j] << "\n";

			// virtual server is found
            if (!sinfoNames[j].compare(0, names.first.size() + 1, names.first)){
                std::cout << "virtual server is found\n";

                std::map<std::string, Location> *loc = (*srv)[i].getLocation();

				// Setting the size_t to zero so the size comparise will always be true for the first match
                std::pair<size_t, std::map<std::string, Location>::iterator> 
						bestMatch(0, loc->begin());

FIX ICI LA RECHERCHE DE NOM

				// Checking each location name, and saving the most long match
				for (std::map<std::string, Location>::iterator it = loc->begin(); it != loc->end(); ++it)
					if (it->first.compare(0, std::string::npos, names.second, 0, it->first.size()) &&
							it->first.size() > bestMatch.first)
					{
						bestMatch.first = it->first.size();
						bestMatch.second = it;
					}

				return &bestMatch.second->second;
			}
        }
	}
	return NULL;
}

std::string *wsTrim(std::string &buf)
{
    if (buf.empty())
        return &buf;
    for (std::string::iterator it = buf.end(); it != buf.begin(); --it)
        if (isspace(*it))
            buf.erase(it);            
    return &buf;
}