# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:24:05 by agrun             #+#    #+#              #
#    Updated: 2023/05/18 12:24:08 by agrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CFLAGS		=	-Wall -Werror -Wextra -g3
CC		=	cc
LR		=	-lreadline
RM		=	rm -f

SRC		=	main brackets utils_1 utils_2 utils_3 utils_4 utils_5 utils_6 \
			utils_7 utils_8 echo_1 echo_2 echo_3 echo_4 echo_5 shell_commands \
			export_unset_1 export_unset_2 export_unset_3 export_unset_4 \
			flag_commands_1 flag_commands_2 flag_commands_3 free access \
			access_utils_1 access_utils_2 access_utils_3 run_built_in_1 \
			run_built_in_2 check_printout_1 check_printout_2 ft_itoa \
			check_for_operators_1 check_for_operators_2 check_for_operators_3 \
			check_for_operators_4 lexer lexer_utils_1 free_tools parser \
			parser_utils_1 redirect_utils_1 parser_utils_2 parser_utils_3 \
			sigint_handler

SRCS		=	$(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

OBJS		=	${SRCS:.c=.o}

DIRSRC		=	./src/
DIRINC		=	./inc/

all:		$(NAME)

$(NAME):	${OBJS}
			${CC} -o ${NAME} ${OBJS} ${LR}

.c.o:
			${CC} ${CFLAGS} -c -I${DIRINC} $< -o ${<:.c=.o}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			
re:			fclean all

.PHONY:		NAME all clean fclean re
