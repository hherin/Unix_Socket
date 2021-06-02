# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 12:56:40 by hherin            #+#    #+#              #
#    Updated: 2021/06/02 15:10:31 by llefranc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	webserv

SRCS		=	main.cpp 
				
OBJS		=	${SRCS:.cpp=.o}

HDRS		=	includes/webserv.hpp

CC			=	clang++

FLAGS		=	-Wall -Werror -Wextra -std=c++98 -fsanitize=address

LIBS		=	parser/lparser.a \
				server/lserver.a \
				utils/lutils.a

SETDEBUG	=	0

all			:	${NAME}

debug		:	SETDEBUG=1	
debug		:	fclean ${NAME} 
				@echo "debug webserv is ready";

%.a			:	sub_makefile
					@make debug=${SETDEBUG} -C ${@D}

%.o			:	%.cpp
				@${CC} ${FLAGS} -o $@ -c $<
				
${NAME}		:	${LIBS} ${OBJS}
				@${CC} -o ${NAME} ${OBJS} ${LIBS} ${FLAGS}
ifeq ($(SETDEBUG), 0)
				@echo "webserv is ready";
endif

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