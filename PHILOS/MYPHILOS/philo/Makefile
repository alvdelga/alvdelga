# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 10:45:43 by alvdelga          #+#    #+#              #
#    Updated: 2025/03/27 11:42:39 by alvdelga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
SRCFILES	:= main.c init.c threads.c philo_observer.c actions.c utils.c
SRC			:= $(addprefix ./src/, $(SRCFILES))
OBJ			:= $(SRC:.c=.o)  # Convierte los archivos fuente .c a archivos objeto .o

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -lpthread
# SANITIZER	:= -fsanitize=thread

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(SANITIZER)

# Regla para compilar cada archivo .c en un archivo .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:		
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re	

delay:
	@python3 delay_o_meter.py

.PHONY: all clean fclean re debug delay
