# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sle-nogu <sle-nogu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 10:14:48 by sle-nogu          #+#    #+#              #
#    Updated: 2025/03/14 12:50:48 by sle-nogu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Minishell
CC=cc
CFLAGS=-Wall -Werror -Wextra

OBJS=$(SRC:.c=.o)

SRC=	main.c \
		mini_libft.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_split.c \
		built_in1.c \
		built_in2.c \
		tablen.c \
		clear.c \
		built_in_utils1.c \
		built_in_utils2.c

# Compilation rules
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

default: all

.PHONY: all re clean fclean
