# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    start.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 14:58:40 by heleneherin       #+#    #+#              #
#    Updated: 2021/04/28 15:26:48 by heleneherin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#! /bin/bash 

make re -C ../

#!/bin/bash


screen -dmS "abc-alpha-32"
sleep 2
echo 'running script command in session..'
screen -S abc-alpha-32 -p abc-alpha-32 -X stuff "script -f /home/user12/scripts/abc-alpha-32.log $(printf \\r)"
sleep 2
echo 'running expect command in session..'
screen -S abc-alpha-32 -p abc-alpha-32 -X stuff "expect /home/user12/scripts/master_dian.sh abc-alpha-32.cisco.com user_id password $(printf \\r)"
expect ./start_telnet.expect localhost 8080

expect ./start_telnet.expect localhost 8081