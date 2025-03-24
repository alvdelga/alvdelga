# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 14:19:21 by druina            #+#    #+#              #
#    Updated: 2025/03/23 21:25:27 by alvdelga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c init.c threads.c monitor.c routine_actions.c utils.c

MANPATH = $(addprefix ./src/, $(SRC))

FLAGS = -pthread

HEADER = ./src/philo.h

# SANITIZER = -fsanitize=thread

all: $(NAME)

$(NAME): $(MANPATH) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(MANPATH) $(SANITIZER)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

debug: FLAGS += -g
debug: re

delay:
	python3 delay_o_meter.py