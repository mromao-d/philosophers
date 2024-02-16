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
SRC_PATH = ./source/
OBJ_PATH = ./objs/
SRC = $(SRC_PATH)args.c $(SRC_PATH)inits.c $(SRC_PATH)logs.c $(SRC_PATH)main.c $(SRC_PATH)threads.c $(SRC_PATH)time.c $(SRC_PATH)utlis.c $(SRC_PATH)utils_2.c $(SRC_PATH)free.c
OBJS = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

#CFLAGS = -Wall -Werror -Wextra -g
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=thread

CC = cc

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME) 1 20 10 10

valgrind: $(NAME)
	valgrind --leak-check=full -s ./$(NAME) 1 2 3 4

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
