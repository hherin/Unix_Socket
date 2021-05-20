/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execGET.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 15:33:37 by hherin            #+#    #+#             */
/*   Updated: 2021/05/20 15:58:20 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Response.hpp"

void lookUpForRoot()
{
    
}


ServerInfo const &serverSearcher(std::vector<ServerInfo> const &srv, std::string const &name)
{
    for (size_t i = 0; i < srv.size(); i++){													// loop for each 
		std::vector<std::string> sinfoNames = srv[i].getNames();
        for (size_t j = 0; j < sinfoNames.size(); j++)
            if (!sinfoNames[i].compare(0, name.size() + 1, name))
                return srv[i];
    }
    return srv[0];
}

// HELENE FONCTION qui store la page a renvoyer dans le body de la reponse
void Response::execGET()
{
	std::vector<std::string> path = stringDelimSplit(_req.getPath(), "/");							// URI requested is splited 
	
    std::map<std::string, std::string>::const_iterator mit = _req.getHeaders().find("host");
    if (mit != _req.getHeaders().end()){
        
    }
        // Look for good server and Do the thing whith good server
    else
        // Do the thing with default

}