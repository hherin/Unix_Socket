/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:29:01 by hherin            #+#    #+#             */
/*   Updated: 2021/04/14 14:04:47 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.hpp"

#include <iostream>

int main(int ac, char **av)
{
	if (ac != 2){
		std::cout << "wrong output" << std::endl;
		exit(0);
	}

	parser p(av[1]);
	
	p.getfile();

	std::vector<server> mainsrv = p.getServer();
	
	for(size_t j = 0; j < mainsrv.size(); j++){
		std::cout << "=========  SERVER " << j << " ============" << std::endl;
		(mainsrv[j].getError().size()) ? std::cout << "error : " << mainsrv[j].getError() << std::endl : 0;

		std::vector<std::string> v0 = mainsrv[j].getNames();
		(mainsrv[j].getNames().size()) ? std::cout << "names : " : 0;
		for (size_t i = 0; i < v0.size(); i++)
			std::cout << v0[i] << " ";
		(mainsrv[j].getNames().size()) ? std::cout << std::endl : 0;

		std::vector<std::string> v1 = mainsrv[j].getMethods();
		std::cout << "methods : ";
		for (size_t i = 0; i < v1.size(); i++)
			std::cout << v1[i] << " ";
		std::cout << std::endl;

		std::vector<std::string> v2 = mainsrv[j].getIndex();
		std::cout << "index : ";
		for (size_t i = 0; i < v2.size(); i++)
			std::cout << v2[i] << " ";
		std::cout << std::endl;
		
		std::vector<int> v3 = mainsrv[j].getPort();
		std::cout << "port : ";
		for (size_t i = 0; i < v3.size(); i++)
			std::cout << v3[i] << " ";
		std::cout << std::endl;
		
		std::cout << "\n------- LOCATION ---------\n";
		std::vector<server> loc = mainsrv[j].getLocation();
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
			
			std::vector<int> v3 = loc[i].getPort();
			(loc[i].getPort().size()) ? std::cout << "port : " : 0;
			for (size_t i = 0; i < v3.size(); i++)
				std::cout << v3[i] << " ";
			(loc[i].getPort().size()) ? std::cout << std::endl : 0;
			
			// std::vector<std::string> v4 = loc[i].getRoot();
			// (loc[i].getRoot().size()) ? std::cout << "root : " : 0;
			// for (size_t i = 0; i < v4.size(); i++)
			// 	std::cout << v4[i] << " ";
			// (loc[i].getRoot().size()) ? std::cout << std::endl : 0;
			
			std::cout << "autoindex : " << loc[i].getAutoIndex() << "\n\n";
		}
		std::cout << "=====================================\n\n";
	}

}