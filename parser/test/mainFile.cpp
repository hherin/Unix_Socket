/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:39:49 by hherin            #+#    #+#             */
/*   Updated: 2021/05/25 14:27:51 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FileParser.hpp"
#include <iostream>
#include <exception>

int main()
{
	ServerInfo srv;
	FileParser outFile("./Makefile");

	// std::cout << "FILE \n" << outFile.getConfigFile() << std::endl;
	try {
	outFile.getConfigFile();}
	catch (std::exception &e){
		std::cerr << e.what();
		exit(EXIT_FAILURE);
	}
	return 0;
}