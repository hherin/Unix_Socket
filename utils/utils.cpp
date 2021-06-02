/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 18:56:49 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/06/02 14:14:47 by llefranc         ###   ########.fr       */
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

std::pair<const std::string, const Location*> 
		matchLocation(std::map<std::string, Location> *loc, const std::string& locName)
{
	std::pair<bool, std::map<std::string, Location>::iterator> 
						bestMatch(0, loc->begin());

	// Checking each location name, and saving the most long match. As we stored location names in a map,
	// they're already sorted form smaller to longest same words, no need to check size: the last match will 
	// be the longest possible match (ex: if searching for "bla", "bl" location will be stored after "b" location)
	for (std::map<std::string, Location>::iterator it = loc->begin(); it != loc->end(); ++it)
		if (!it->first.compare(0, std::string::npos, locName, 0, it->first.size()))
		{
			bestMatch.first = true;
			bestMatch.second = it;
		}
	
	// Case there was no match
	if (!bestMatch.first)
		return std::pair<const std::string, const Location*>("", 0);

	return std::pair<const std::string, const Location*>(bestMatch.second->first, &bestMatch.second->second);
}

// srv = list of virtual server for one port, names.first = name of virtual server, names.second = location name
std::pair<const std::string, const Location*> 
		locationSearcher(std::vector<ServerInfo> *srv, std::pair<std::string, std::string> const &names)
{
	// loop for each virtual server for a specific port
	for (size_t i = 0; i < srv->size(); i++){
	
		std::vector<std::string> sinfoNames = (*srv)[i].getNames();

		// loop for each names in each server block
        for (size_t j = 0; j < sinfoNames.size(); j++)
		{
			// virtual server is found
            if (!sinfoNames[j].compare(0, names.first.size() + 1, names.first))
			{
				#if DEBUG
					
				#endif
                return matchLocation((*srv)[i].getLocation(), names.second);
			}
        }
	}
	
	// Case no server_names match, using default server block (the first one)
	return matchLocation((*srv)[0].getLocation(), names.second);
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

void printLog(const std::string &msg, const std::string& addInfo)
{
	// current date and time on the current system
	time_t now = time(0);

	// convert now to string form and removing '\n'
	std::string date(ctime(&now));
	date.resize(date.length() - 1);

	std::cout << "[" << date << "] " << msg;

	#if defined DEBUG
		if (!addInfo.empty())
			std::cout << "-------------------------\n" << addInfo << "-------------------------\n\n";
	#else
		(void)addInfo;
	#endif
}