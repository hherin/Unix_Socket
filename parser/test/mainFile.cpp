/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:39:49 by hherin            #+#    #+#             */
/*   Updated: 2021/04/27 13:24:19 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../FileParser.hpp"
#include <iostream>

int main()
{
	ServerInfo srv;
	FileParser outFile("./Makefile");

	// std::cout << "FILE \n" << outFile.getConfigFile() << std::endl;
	outFile.getConfigFile();
	return 0;
}