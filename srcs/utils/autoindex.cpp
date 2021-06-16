/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hherin <hherin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:42:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/16 19:08:43 by hherin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "../includes/webserv.hpp"

#include <unistd.h>

// std::string const &autoIndexDisplayer(std::string uri)
// {
// 	int pid;
// 	int fd[2];
// 	static std::string displayList;
// 	displayList.clear();


// 	pipe(fd);
// 	pid = fork();
	
// 	if (!pid){
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		std::string cmd = (std::string("php ") + getcwd(NULL, 0)) + "/autoindex.php " + uri;
// 		std::system(cmd.c_str());
// 		return displayList;
// 	}
// 	else if (pid > 0){
// 		close(fd[1]);
	
// 		char buf[BUFFER_SIZE_CGI_PIPE + 1] = {0};
// 		while (read(fd[0], buf, BUFFER_SIZE_CGI_PIPE) > 0)
// 		{
// 			displayList += buf;
// 			memset(buf, 0, BUFFER_SIZE_CGI_PIPE + 1);
// 		}
// 		displayList += buf;

// 		close(fd[0]);	
// 	}
// 	else {
// 		close(fd[1]); close(fd[0]);
// 		throw std::runtime_error("Error in fork occurs\n");
		
// 	}
// 	return displayList;
// }

void autoIndexDisplayer(std::string const &uri, std::string &displayList)
{
	int fd[2];
	
	pipe(fd);
	int coutSave = dup(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	
	std::string cmd = "php " + (getcwd(NULL, 0) + ("/autoindex.php " + uri)) ;
	std::cerr << "avant std::system\n";
	std::cout << std::system(cmd.c_str());
	std::cerr << "apres system\n";	
	char buf[BUFFER_SIZE_CGI_PIPE + 1] = {0};
	// while (read(fd[0], buf, BUFFER_SIZE_CGI_PIPE) > 0)
	read(fd[0], buf, BUFFER_SIZE_CGI_PIPE);
	
		displayList += buf;
		memset(buf, 0, BUFFER_SIZE_CGI_PIPE + 1);
	
	// displayList += buf;

	close(fd[0]);	
	dup2(STDOUT_FILENO, coutSave);
	
}

int main(void)
{
	std::cout << autoIndexDisplayer("./") << "\n";
}