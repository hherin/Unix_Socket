# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 12:56:40 by hherin            #+#    #+#              #
#    Updated: 2021/04/23 15:12:41 by heleneherin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv

SRCS		=	main.cpp server/HttpServer.cpp parser/ServerInfo.cpp parser/FileParser.cpp \
				server/ServerSocket.cpp server/ClientSocket.cpp

OBJS		=	${SRCS:.cpp=.o}

HDRS		=	includes/http.hpp server/HttpServer.hpp server/ServerSocket.hpp \
				server/ClientSocket.hpp

CC			=	clang++

FLAGS		=	-Wall -Werror -Wextra -std=c++98 -fsanitize=address


all			:	${NAME}

${NAME}		:	${OBJS}
				@${CC} ${FLAGS} -o ${NAME} ${OBJS}
				@echo "webserv is ready";

%.o			:	%.cpp
				@${CC} ${FLAGS} -o $@ -c $<

${OBJS}		:	${HDRS}

clean		:
				@rm -rf $(OBJS) 

fclean		:	clean
				@rm -rf ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re