/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:29:01 by hherin            #+#    #+#             */
/*   Updated: 2021/04/13 12:01:25 by heleneherin      ###   ########.fr       */
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
		std::cout << "SERVER " << j << std::endl;
		std::cout << "PORT : " << mainsrv[j].getPort() << std::endl;
		std::cout << "ERROR : " << mainsrv[j].getError() << std::endl;

		std::vector<std::string> v0 = mainsrv[j].getNames();
		std::cout << "NAMES : ";
		for (size_t i = 0; i < v0.size(); i++)
			std::cout << v0[i] << " ";
		std::cout << std::endl;

		std::vector<std::string> v1 = mainsrv[j].getMethods();
		std::cout << "METHODS : ";
		for (size_t i = 0; i < v1.size(); i++)
			std::cout << v1[i] << " ";
		std::cout << std::endl;

		std::vector<std::string> v2 = mainsrv[j].getIndex();
		std::cout << "INDEX : ";
		for (size_t i = 0; i < v2.size(); i++)
			std::cout << v2[i] << " ";
		std::cout << std::endl;
		std::cout << "=====================================\n\n";
	}

}