# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrun <agrun@student.42berlin.de>         +#+  +:+       +#+          #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/23 12:24:05 by agrun             #+#    #+#              #
#    Updated: 2023/09/23 12:24:08 by agrun            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.cpp BitcoinExchange.cpp
OBJ		= $(SRC:.cpp=.o)
CC		= c++
RM		= rm -f
CFLAGS		= -Wall -Wextra -Werror -std=c++98

NAME 		= btc

all:		$(NAME)

%.o:	%.cpp
		$(CC) $(CFLAGS) -c $^ -o $@

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean $(NAME)

.PHONY: 	all clean fclean re
