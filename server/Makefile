# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hherin <hherin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/27 14:27:30 by hherin            #+#    #+#              #
#    Updated: 2021/05/20 15:36:48 by hherin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	lserver.a

SRCS		=	HttpServer.cpp \
				ServerSocket.cpp \
				ClientSocket.cpp \
				Request.cpp \
				Response.cpp \
				methods/execGET.cpp

OBJS		=	${SRCS:.cpp=.o}

HDRS		=	HttpServer.hpp \
				ServerSocket.hpp \
				ClientSocket.hpp \
				Request.hpp \
				Response.hpp \
				msg_format/StatusLine.hpp \
				msg_format/RequestLine.hpp \
				msg_format/Body.hpp

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