# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hherin <hherin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 14:27:30 by hherin            #+#    #+#              #
#    Updated: 2021/04/27 17:12:20 by hherin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lutils.a

SRCS		=	utils.cpp \

OBJS		=	${SRCS:.cpp=.o}

HDRS		=

FLAGS		=	-Wall -Werror -Wextra -std=c++98 -fsanitize=address

all			:	${NAME}

%.o			:	%.cpp
				@${CC} ${FLAGS} -o $@ -c $<

${NAME}		:	${OBJS} 
				@ar rcs ${NAME} ${OBJS}
				@ranlib ${NAME}

${OBJS}			:	${HDRS}

clean			:
					@rm -rf *.o ../*.o

fclean			:	clean
					@rm -rf ${NAME}

re				:	fclean all

.PHONY			:	all clean fclean re