# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seb <seb@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/26 10:14:48 by sle-nogu          #+#    #+#              #
#    Updated: 2025/03/11 14:20:15 by seb              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Minishell
CC=cc
CFLAGS=-Wall -Werror -Wextra

OBJS=$(SRC:.c=.o)

SRC=	Minishell_built_in.c \
		mini_libft.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_split.c

# Compilation rules
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

default: all

.PHONY: all re clean fclean
