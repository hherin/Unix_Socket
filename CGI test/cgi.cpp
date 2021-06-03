/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:59:43 by heleneherin       #+#    #+#             */
/*   Updated: 2021/06/02 17:52:33 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>
# include <fstream>

int main(void)
{
	std::string ret;
	std::streambuf *redirect, *backup;
	std::ifstream output;
		
	backup = std::cout.rdbuf();
	redirect = output.rdbuf();
	std::cout.rdbuf(redirect);
	pid_t pid = fork();

	if (!pid){
		if (execve("./exec.cgi", NULL, NULL) < 0){
			std::cerr << "Error with execve occur\n"; return 1;
		}
	}
	else if (pid > 0){
		output >> ret;
		std::cout.rdbuf(backup);
	}
	else{
		std::cerr << "Error in fork occur\n"; return 1;
	}

	std::cout << "From the main \n\n" <<  ret << "\n";
	return 0;
}