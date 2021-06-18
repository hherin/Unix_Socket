/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:42:35 by hherin            #+#    #+#             */
/*   Updated: 2021/06/18 09:56:39 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
#include "../includes/webserv.hpp"

void autoIndexDisplayer(std::string const &uri, std::string* displayList)
{
	int fd[2];
	
	pipe(fd);
	int coutSave = dup(STDOUT_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	
    char *path;
    if (!(path = getcwd(NULL, 0)))
        throw StatusLine(500, REASON_500, "getcwd function in autoIndexDisplayer failed\n");

	std::string exec_path = "./bin/php " + (path + ("/srcs/utils/autoindex.php " + uri));
	std::system(exec_path.c_str());

    // Restoring STDOUT and closing the last fd[1], so read will get EOF signal
    dup2(coutSave, STDOUT_FILENO);
    close(coutSave);

	char buf[CGI_BUFFER_SIZE + 1] = {0};

	while (read(fd[0], buf, CGI_BUFFER_SIZE) > 0){	
		*displayList += buf;
		memset(buf, 0, CGI_BUFFER_SIZE + 1);
	}

	*displayList += buf;

	close(fd[0]);
    free(path);
}
