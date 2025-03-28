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

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -pthread
SANITIZER	:= -fsanitize=thread -g

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

test: $(NAME)
	@echo "Running tests..."
	@correct=0; \
	incorrect=0; \
	failed_tests=""; \
	num=20; \
	trap 'echo "Tests interrupted"; kill $$!; exit 1' INT; \
	for args in "4 410 200 200" "5 800 200 200" "5 600 150 150" "100 800 200 200" "105 800 200 200" "200 800 200 200"; do \
		echo "[+] Running with parameters: $$args"; \
		sleep 3; \
		./$(NAME) $$args > /dev/null 2>&1 & pid=$$!; \
		sleep $$num; \
		if ps -p $$pid > /dev/null; then \
			echo "Done: Execution of './$(NAME) $$args' ran for $$num seconds successfully."; \
			kill $$pid; \
			num=$$((num)); \
			wait $$pid 2>/dev/null; \
			correct=$$((correct + 1)); \
		else \
			echo "Error: Execution of './$(NAME) $$args' finished before $$num seconds."; \
			incorrect=$$((incorrect + 1)); \
			failed_tests="$$failed_tests $$args"; \
			# break; \
		fi; \
		sleep 2; \
	done; \
	echo "=============================="; \
	echo "Test Results:"; \
	echo "Correct Tests: $$correct"; \
	echo "Incorrect Tests: $$incorrect"; \
	echo "Failed Tests: $$failed_tests"; \
	echo "=============================="


delay:
	@python3 delay_o_meter.py

.PHONY: all clean fclean re debug test delay
