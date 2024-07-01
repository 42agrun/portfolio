# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumann <lbaumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/16 16:25:57 by lbaumann          #+#    #+#              #
#    Updated: 2023/09/06 15:22:24 by lbaumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

#ADD BACK FLAGS
CC = cc
CFLAGS = -Wall -Werror -Wextra
MAKEFLAGS   += --no-print-directory

ifeq ($(NOFLAGS), 1)
CFLAGS =
endif

ifeq ($(DEBUG), 1)
CFLAGS = -Wall -Werror -Wextra -g
all: rmobj
endif

BONUS_TARGET = 0

ifeq ($(filter bonus,$(MAKECMDGOALS)),bonus)
BONUS_TARGET = 1
endif

ifeq ($(BONUS_TARGET), 1)
CFLAGS += -D BONUS=1
endif

SRCDIR := src
INCDIR := inc
OBJDIR := obj
LIBFTDIR := libft

HEADERS = -I $(INCDIR)

#libft
LIBFT = $(LIBFTDIR)/libft.a
LIBFTINCL = -L$(LIBFTDIR) -lft

#MLX
MLX = minilibx-linux/libmlx.a
MLXINCL	= -L ./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

LDFLAGS = $(LIBFTINCL)

SRCS = \
	main \
	main_utils \
	ft_error \
	parser/check_map \
	parser/check_map_2 \
	parser/check_map_3 \
	parser/check_colors \
	parser/extract_map \
	parser/extract_map_2 \
	parser/ft_str_join \
	parser/map_read_utils \
	parser/gnl_utils \
	game/root_setup \
	game/render_setup \
	game/game_setup \
	game/game_destroy \
	game/game_controls \
	game/door_controls \
	game/player_movement \
	game/mlx_utils \
	game/mouse_controls \
	minimap/minimap \
	minimap/minimap_helper \
	raycast/raycast \
	raycast/raycast_setup \
	raycast/texture \
	math/vector_operations \
	math/vector_manipulation \
	line/line \

SRCS		:= $(SRCS:%=$(SRCDIR)/%.c)
OBJS		:= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(MLX) $(NAME)

bonus: clean $(MLX) $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(MLXINCL) -o $(NAME_BONUS)
	$(info CREATED $(NAME_BONUS))

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(MLXINCL) -o $(NAME) 
	$(info CREATED $(NAME))

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<
	$(info CREATED $@)

$(LIBFT):
	if [ ! -d "libft" ]; then git clone https://github.com/leonyannick/libft.git; fi
	$(MAKE) -C $(LIBFTDIR)

#delete obj files and call clean in libft Makefile
clean:
	rm -rf $(OBJDIR)
	rm -rf $(OBJDIR_BONUS)
	$(MAKE) clean -C $(LIBFTDIR)
	$(info DELETED obj)

#call clean in mlx Makefile
cleanmlx:
	$(MAKE) clean -C minilibx-linux

#call fclean in libft, cleanmlx, removes executable
fclean: clean cleanmlx
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) fclean -C $(LIBFTDIR)
	$(info DELETED $(NAME))

rmobj:
	rm -rf $(OBJDIR)

#if mlx folder is not existing it downloads it from the intra extracts it and deletes the compressed file
#it gives it execution rights if they are missing
#calls make from mlx Makefile
$(MLX):
	if [ ! -d "minilibx-linux" ]; then \
	wget https://cdn.intra.42.fr/document/document/17607/minilibx-linux.tgz; \
	tar -xzf minilibx-linux.tgz; \
	rm minilibx-linux.tgz; fi
	if [ ! -x "minilibx-linux/configure" ]; then chmod ugo+rwx minilibx-linux/configure; fi
	$(MAKE) -C minilibx-linux
	$(info COMPILED MLX)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
