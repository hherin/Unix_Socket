# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hherin <hherin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 12:56:40 by hherin            #+#    #+#              #
#    Updated: 2021/04/22 14:28:55 by hherin           ###   ########.fr        #
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

HDRS			=	../../includes/FileParser.hpp ../../includes/ServerInfo.hpp

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