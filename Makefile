# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/01 12:56:40 by hherin            #+#    #+#              #
#    Updated: 2021/06/02 12:44:38 by llefranc         ###   ########.fr        #
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

all			:	${NAME}

debug		:	${LIBS} ${OBJS}
				@${CC} -o ${NAME} ${OBJS} ${LIBS} ${FLAGS}
				@echo "debug webserv is ready";

%.a			:	sub_makefile
				@make -C ${@D}
				
%.o			:	%.cpp
				@${CC} ${FLAGS} -o $@ -c $<
				
${NAME}		:	${LIBS} ${OBJS}
				@${CC} -o ${NAME} ${OBJS} ${LIBS} ${FLAGS}
				@echo "webserv is ready";

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