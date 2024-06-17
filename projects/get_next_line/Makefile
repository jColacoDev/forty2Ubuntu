# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 15:12:37 by joao-rde          #+#    #+#              #
#    Updated: 2024/06/17 19:57:47 by joao-rde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lib.a
CC = cc
CFLAGS= -Wall -Wextra -Werror -g3
SOURCES = get_next_line_bonus.c get_next_line.c get_next_line_utils.c
OBJECTS	= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rcs $(NAME) $(OBJECTS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)
	touch bonus

clean:
	rm -f $(OBJECTS) bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
