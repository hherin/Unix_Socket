/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainConfig.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:29:01 by hherin            #+#    #+#             */
/*   Updated: 2021/06/18 10:08:09 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FileParser.hpp"

#include <iostream>

int main(int ac, char **av)
{
	if (ac != 2){
		std::cout << "wrong output" << std::endl;
		exit(0);
	}

	FileParser config(av[1]);
	try{
		std::map<int, std::vector<ServerInfo> > map = config.getConfigFile();
		
		for (std::map<int, std::vector<ServerInfo> >::iterator it = map.begin(); it != map.end(); it++){
			std::cout << "===========================================================\n";
			std::cout << "=========================== " << it->first << " =========================\n";
			std::cout << "============================================================\n";
			for(size_t j = 0; j < it->second.size(); j++){
				std::cout << "=========  SERVER " << j << " ============" << std::endl;
				(it->second[j].getError().size()) ? std::cout << "error : " << it->second[j].getError() << std::endl : 0;

				std::vector<std::string> v0 = it->second[j].getNames();
				(it->second[j].getNames().size()) ? std::cout << "names : " : 0;
				for (size_t i = 0; i < v0.size(); i++)
					std::cout << v0[i] << " ";
				(it->second[j].getNames().size()) ? std::cout << std::endl : 0;

				std::cout << "host : " << it->second[j].getHost() << std::endl;

				std::cout << "Max body : " << it->second[j].getMaxClientsBS() << std::endl;
				
				std::cout << "port : " << it->second[j].getPort() << "\n";
				
				std::cout << "\n------- LOCATION ---------\n";
				std::map<std::string, Location> loc = *(it->second[j].getLocation());
				for (std::map<std::string, Location>::iterator it2 = loc.begin(); it2 != loc.end(); it2++){
					
					std::cout << "LOC " << it2->first << ": \n";
					std::cout << "AutoIndex : " << it2->second.getAutoIndex() << std::endl;
					(it2->second.getRoot().size()) ? std::cout << "root : " << it2->second.getRoot() << std::endl : 0;
					std::vector<std::string> v1 = it2->second.getMethods();
					(it2->second.getMethods().size()) ? std::cout << "methods : " : 0;
					for (size_t i = 0; i < v1.size(); i++)
						std::cout << v1[i] << " ";
					(it2->second.getMethods().size()) ? std::cout << std::endl : 0;

					std::vector<std::string> v2 = it2->second.getIndex();
					(it2->second.getIndex().size()) ? std::cout << "index : " : 0;
					for (size_t i = 0; i < v2.size(); i++)
						std::cout << v2[i] << " ";
					(it2->second.getIndex().size()) ? std::cout << std::endl : 0;

					std::map<std::string, std::string> v3 = it2->second.getCgiExe();
					(it2->second.getCgiExe().size()) ? std::cout << "cgi : \n" : 0;
					for (std::map<std::string, std::string>::const_iterator it = v3.begin(); it != v3.end(); it++){
						std::cout << "* " << it->first << " " << it->second << "\n";
					}
					(it2->second.getCgiExe().size()) ? std::cout << std::endl : 0;				
					(it2->second.getRedirect().size()) ? std::cout << it2->second.getRedirect() << "\n" : 0;
					std::cout << "\n\n";

				}
			std::cout << "=====================================\n\n";
			}
		}
	}
	catch (const char *e){
		std::cerr << e << "\n";
		exit(EXIT_FAILURE);
	}
}