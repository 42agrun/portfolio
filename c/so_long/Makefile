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

NAME		= so_long

CFLAGS		=	-Wall -Werror -Wextra
CC		= 	cc
RM 		=	rm -f

MLX		= 	-L ./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

SRC		= 	main check_map check_map_path ft_strjoin ft_error \
			gnl_utils so_long_utils flood_map ft_itoa root_setup \
			render_setup game_setup mlx_utils game_destroy \
			game_controls update_game player_move

SRCS		= $(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

OBJS 		= ${SRCS:.c=.o} ${LIBX:.c=.o}

DIRSRC		= ./src/
DIRINC		= ./inc/

all:		MLX_MAKE $(NAME)

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${MLX} -o ${NAME}

MLX_MAKE:		$(shell chmod ugo=rwx minilibx-linux/configure)
			#$(shell make -C minilibx-linux)

.c.o:
			${CC} ${CFLAGS} -c -I${DIRINC} $< -o ${<:.c=.o}

clean:
			${RM} ${OBJS}
			rm -f minilibx-linux/obj/*.o

fclean:		clean
			${RM} ${NAME}
			rm -f minilibx-linux/libmlx.a
			rm -f minilibx-linux/libmlx_Linux.a

re:			fclean all

.PHONY: 	all clean fclean re
