/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainFile.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:39:49 by hherin            #+#    #+#             */
/*   Updated: 2021/04/22 14:27:37 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/FileParser.hpp"
#include <iostream>

int main()
{
	FileParser outFile("./Makefile");

	std::cout << "FILE \n" << outFile.getOutputFile() << std::endl;
	return 0;
}