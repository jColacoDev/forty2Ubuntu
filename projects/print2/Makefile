# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 15:12:37 by joao-rde          #+#    #+#              #
#    Updated: 2024/06/05 17:27:37 by joao-rde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS= -Wall -Wextra -Werror -g3
SOURCES = ft_printf.c libft.c libft2.c libft3.c libft4.c libft5.c utils.c utils1.c utils2.c utils3.c
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