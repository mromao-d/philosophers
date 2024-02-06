# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 16:01:38 by mromao-d          #+#    #+#              #
#    Updated: 2024/02/06 16:33:15 by mromao-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philos
# SRC = *.c
SRC = args.c inits.c logs.c main.c threads.c time.c utlis.c
OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

run: $(NAME)
	valgrind --tool=helgrind ./$(NAME) 2 2 3 4

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
