# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    start.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 14:58:40 by heleneherin       #+#    #+#              #
#    Updated: 2021/05/03 19:17:13 by heleneherin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#! /bin/bash 

screen -S webserv -d -m -X ../webserv parser/test/conf > OUTPUT-WEB
ls -d -1 "$PWD"/req/* > ls_files
expect -df ./telnet.expect localhost 8080 > OUTPUT-EXP
