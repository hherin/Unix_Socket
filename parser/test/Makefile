# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heleneherin <heleneherin@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 12:56:40 by hherin            #+#    #+#              #
#    Updated: 2021/04/23 15:48:27 by heleneherin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMEConfig		=	parserConfig

NAMEfile		=	parserFile

SRCS			=	../ServerInfo.cpp ../FileParser.cpp

SRCSCONF		=	mainConfig.cpp

SRCSFILE		=	mainFile.cpp

OBJS			=	${SRCS:.cpp=.o}

OBJSCONF		=	${SRCSCONF:.cpp=.o}

OBJSFILE		=	${SRCSFILE:.cpp=.o}

HDRS			=	FileParser.hpp ServerInfo.hpp

CC				=	clang++

FLAGS			=	-Wall -Werror -Wextra -std=c++98 -fsanitize=address


all				:	${NAMEconfig} ${NAMEfile}

config			:	${NAMEconfig}

file			:	${NAMEfile}

%.o				:	%.cpp
					${CC} ${FLAGS} -o $@ -c $<

${NAMEconfig}	:	${OBJS} ${OBJSCONF}
					@${CC} ${FLAGS} -o ${NAMEconfig} ${OBJSCONF} ${OBJS}
					@echo "parserConfig is ready";

${NAMEfile}		:	${OBJSFILE} ${OBJS} 
					${CC} ${FLAGS} -o ${NAMEfile} ${OBJSFILE} ${OBJS}
					@echo "parserFile is ready";


${OBJS}			:	${HDRS}

clean			:
					@rm -rf *.o ../*.o

fclean			:	clean
					@rm -rf ${NAMEconfig} ${NAMEfile}

re				:	fclean all

.PHONY			:	all clean fclean re