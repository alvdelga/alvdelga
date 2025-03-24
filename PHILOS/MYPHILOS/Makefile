# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 10:45:43 by alvdelga          #+#    #+#              #
#    Updated: 2025/03/24 12:29:21 by alvdelga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
SRCFILES	:= main.c init.c threads.c monitor.c routine_actions.c utils.c
SRC			:= $(addprefix ./src/, $(SRCFILES))

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -pthread
SANITIZER	:= -fsanitize=thread

# 🧠 Build target
$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(SANITIZER)

all: $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all
debug: CFLAGS += -g
debug: re

# ⏱ Extra utility (custom command)
delay:
	@python3 delay_o_meter.py

.PHONY: all clean fclean re debug delay