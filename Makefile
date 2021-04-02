# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hherin <hherin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 12:56:40 by hherin            #+#    #+#              #
#    Updated: 2021/04/02 17:20:39 by hherin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv

SRCS		=	main.cpp server.cpp

OBJS		=	${SRCS:.cpp=.o}

HDRS		=	server.hpp

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
				@rm -rf *.o

fclean		:	clean
				@rm -rf ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re