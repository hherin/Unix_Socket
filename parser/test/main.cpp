/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:29:01 by hherin            #+#    #+#             */
/*   Updated: 2021/04/12 18:12:41 by hherin           ###   ########.fr       */
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
		std::cout << "=====================================\n\n";
	}

	// for (std::vector<server>::iterator it = mainsrv.begin(); it != mainsrv.end(); it++){
	// 	std::cout << "SERVER " << i << std::endl;
	// 	std::cout << "PORT : " << (*it).getPort() << std::endl;
	// 	std::cout << "ERROR : " << (*it).getError() << std::endl;

	// 	std::vector<std::string> v0 = (*it).getNames();
	// 	std::cout << "NAMES : ";
	// 	for (std::vector<std::string>::iterator ite = v0.begin(); ite != v0.end(); it++)
	// 		std::cout << (*ite) << " ";
	// 	std::cout << std::endl;

	// 	std::cout << "HOST : " << (*it).getHost() << std::endl;
	// }
}