/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:59:43 by heleneherin       #+#    #+#             */
/*   Updated: 2021/05/31 17:21:41 by heleneherin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>


int main(int ac, char **av)
{
	if (ac != 2){
		std::cerr << "Miss a file\n"; return 1;
	}
	pid_t pid = fork();

	if (!pid){
		if (execve(av[1], NULL, NULL) < 0){
			std::cerr << "Error with execve occur\n"; return 1;
		}
		// execve
	}
	else if (pid > 0){
		(void)av;
		// daddy issue
	}
	else{
		std::cerr << "Error in fork occur\n"; return 1;
	}

	return 0;
}