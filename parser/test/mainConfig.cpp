/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainConfig.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:29:01 by hherin            #+#    #+#             */
/*   Updated: 2021/04/27 14:08:55 by hherin           ###   ########.fr       */
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

			std::vector<std::string> v1 = it->second[j].getMethods();
			std::cout << "methods : ";
			for (size_t i = 0; i < v1.size(); i++)
				std::cout << v1[i] << " ";
			std::cout << std::endl;

			std::vector<std::string> v2 = it->second[j].getIndex();
			std::cout << "index : ";
			for (size_t i = 0; i < v2.size(); i++)
				std::cout << v2[i] << " ";
			std::cout << std::endl;
			
			std::cout << "port : " << it->second[j].getPort() << "\n";
			
			std::cout << "\n------- LOCATION ---------\n";
			std::vector<ServerInfo> loc = it->second[j].getLocation();
			for (unsigned int i = 0; i < loc.size(); i++){
				std::cout << "LOC " << i << ": \n";
				(loc[i].getError().size()) ? std::cout << "error : " << loc[i].getError() << std::endl : 0;
				(loc[i].getRoot().size()) ? std::cout << "root : " << loc[i].getRoot() << std::endl : 0;

				std::vector<std::string> v0 = loc[i].getNames();
				(loc[i].getNames().size()) ? std::cout << "names : " : 0;
				for (size_t i = 0; i < v0.size(); i++)
					std::cout << v0[i] << " ";
				(loc[i].getNames().size()) ? std::cout << std::endl : 0;

				std::vector<std::string> v1 = loc[i].getMethods();
				(loc[i].getMethods().size()) ? std::cout << "methods : " : 0;
				for (size_t i = 0; i < v1.size(); i++)
					std::cout << v1[i] << " ";
				(loc[i].getMethods().size()) ? std::cout << std::endl : 0;

				std::vector<std::string> v2 = loc[i].getIndex();
				(loc[i].getIndex().size()) ? std::cout << "index : " : 0;
				for (size_t i = 0; i < v2.size(); i++)
					std::cout << v2[i] << " ";
				(loc[i].getIndex().size()) ? std::cout << std::endl : 0;
				
				(loc[i].getPort() >= 0) ? std::cout << "port : " << loc[i].getPort() << "\n" : 0;
				
				
				std::cout << "autoindex : " << loc[i].getAutoIndex() << "\n\n";
			}
		std::cout << "=====================================\n\n";
		}
	}
}