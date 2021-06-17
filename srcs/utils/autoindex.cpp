/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:42:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/17 15:38:25 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "../includes/webserv.hpp"

void autoIndexDisplayer(std::string const &uri, std::string &displayList)
{
	int fd[2];
	
	pipe(fd);
	int coutSave = dup(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	
	std::string cmd = "php " + (getcwd(NULL, 0) + ("/autoindex.php " + uri)) ;
	std::system(cmd.c_str());
	char buf[CGI_BUFFER_SIZE + 1] = {0};
	while (read(fd[0], buf, CGI_BUFFER_SIZE) == CGI_BUFFER_SIZE){	
		displayList += buf;
		memset(buf, 0, CGI_BUFFER_SIZE + 1);
	}
	displayList += buf;

	close(fd[0]);	
	dup2(coutSave, STDOUT_FILENO);
}
