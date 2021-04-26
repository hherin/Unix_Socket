/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:39:49 by hherin            #+#    #+#             */
/*   Updated: 2021/04/23 15:48:15 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileParser.hpp"
#include <iostream>

int main()
{
	FileParser outFile("./Makefile");

	std::cout << "FILE \n" << outFile.getOutputFile() << std::endl;
	return 0;
}