# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    start.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 14:58:40 by heleneherin       #+#    #+#              #
#    Updated: 2021/05/04 14:06:16 by heleneherin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#! /bin/bash 

../webserv ../parser/test/conf > OUTPUT-WEB 2>&1 &
ls -d -1 "$PWD"/req/* > ls_files
expect -df ./telnet.expect localhost 8080 > OUTPUT-EXP 2>&1
