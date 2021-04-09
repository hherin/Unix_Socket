/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:06:51 by hherin            #+#    #+#             */
/*   Updated: 2021/04/09 14:19:24 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.hpp"
#include <iostream>

parser::parser(char *filepath) : conf(filepath) 
{
	file.open(conf.c_str());
}

parser::~parser() {}

void parser::getfile()
{
	
	while (file >> buf)
	{
		// std::cout << "LINE " << i++ << std::endl;
		std::cout << buf << std::endl;	
		if (buf == "choose")
		{
			file >> buf;
			std::cout << "\tNEXT " << buf << std::endl;
		}
	}
	
	// std::cout << std::endl << std::endl << "BUFFER\n" << buf << std::endl;
}

int main(int ac, char **av)
{
	if (ac != 2){
		std::cout << "wrong output" << std::endl;
		exit(0);
	}
	parser p(av[1]);

	p.getfile();
}