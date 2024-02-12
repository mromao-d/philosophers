# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 16:01:38 by mromao-d          #+#    #+#              #
#    Updated: 2024/02/11 14:04:01 by mromao-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
# SRC = *.c
SRC = args.c inits.c logs.c main.c threads.c time.c utlis.c utils_2.c
OBJS = $(SRC:.c=.o)

#CFLAGS = -Wall -Werror -Wextra -g
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread

CC = cc

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

run: $(NAME)
#	valgrind --tool=helgrind ./$(NAME) 1 20 10 10
	./$(NAME) 1 20 10 10

valgrind: $(NAME)
	valgrind --leak-check=full -s	 ./$(NAME) 1 2 3 4

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
