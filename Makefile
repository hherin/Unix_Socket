# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hherin <hherin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 12:56:40 by hherin            #+#    #+#              #
#    Updated: 2021/06/14 16:52:57 by hherin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv

SRCS		=	srcs/main.cpp 
				
OBJS		=	${SRCS:.cpp=.o}

HDRS		=	srcs/includes/webserv.hpp

CC			=	clang++

FLAGS		=	-Wall -Werror -Wextra -std=c++98 -fsanitize=address

LIBS		=	srcs/parser/lparser.a \
				srcs/server/lserver.a \
				srcs/utils/lutils.a

SETDEBUG	=	0

all			:	${NAME}

debug		:	SETDEBUG=1
debug		:	fclean ${NAME}
				@make clean


%.a			:	sub_makefile
					@make debug=${SETDEBUG} -C ${@D}

%.o			:	%.cpp
				@${CC} -DDEBUG=${SETDEBUG} ${FLAGS} -o $@ -c $<
				
${NAME}		:	${LIBS} ${OBJS}	
				@${CC} -o ${NAME} ${OBJS} ${LIBS} ${FLAGS}
				@echo "webserv is ready";
# ifeq ($(SETDEBUG), 0)
# 					@echo "webserv is ready";
# else
# 					@echo "debug webserv is ready";
# endif

${OBJS}		:	${HDRS}

clean		:
				@for lib in ${LIBS}; do \
					make clean -C $$(dirname $$lib) ;\
				done
				@rm -rf $(OBJS) 

fclean		:	clean
				@for lib in ${LIBS}; do \
					make fclean -C $$(dirname $$lib) ;\
				done
				@rm -rf ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re sub_makefile