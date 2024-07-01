# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 13:41:58 by agrun             #+#    #+#              #
#    Updated: 2023/03/03 14:13:40 by agrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap

CFLAGS		=	-Wall -Werror -Wextra
CC		= 	cc
RM 		=	rm -f

SRC		= 	main check_dupes check_input ft_atoi ft_split \
			push_swap sort_utils sort_utils_2 sort_utils_3 \
			sorting_algo sorting_algo_2 check_zero define_head \
			combine_args

SRCS		= $(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

OBJS 		= ${SRCS:.c=.o}

DIRSRC		= ./src/
DIRINC		= ./include/

all:		$(NAME)

$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS}

.c.o:
			${CC} ${CFLAGS} -c -I${DIRINC} $< -o ${<:.c=.o}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re
