/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:20:06 by druina            #+#    #+#             */
/*   Updated: 2025/03/27 11:58:01 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

# define MAX_PHILO 300
# define RESET    "\033[0m"
# define RED      "\033[31m"
# define GREEN    "\033[32m" 

typedef struct s_philo
{
	pthread_t		thread;
	int				id;

	//Protegidas por meal_lock
	bool			eating;         // Indica si el filósofo está comiendo
	int				meals_eaten;    // Cuántas veces ha comido
	size_t			last_meal;      // Último tiempo en que comió

	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;

	pthread_mutex_t	*r_fork;       // Tenedor izquierdo
	pthread_mutex_t	*l_fork;       // Tenedor derecho

	// Mutex compartidos
	pthread_mutex_t	*write_lock;   // Protege los mensajes en consola
	pthread_mutex_t	*dead_lock;    // Protege el acceso a dead_flag
	pthread_mutex_t	*meal_lock;    // Protege eating, meals_eaten, last_meal
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

// Main functions
int					check_arg_content(char *arg);
int					check_valid_args(char **argv);
void				destory_all(char *str, t_program *program,
						pthread_mutex_t *forks);

// Initialization
int				init_program(t_program *program, t_philo *philos);
int				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_philos(t_philo *philoso, t_program *program,
						pthread_mutex_t *forks, char **argv);
void				init_input(t_philo *philo, char **argv);

// Threads
int					thread_create(t_program *program, pthread_mutex_t *forks);
void				*philo_observer(void *pointer);
void				*philo_routine(void *pointer);

// Actions
void				eat(t_philo *philo);
void				dream(t_philo *philo);
void				think(t_philo *philo);

// observer utils
int					dead_loop(t_philo *philo);
int					check_all_ate(t_philo *philos);
int					check_dead(t_philo *philos);
int					philosopher_dead(t_philo *philo, size_t time_to_die);

// Utils
int					ft_atoi(const char *str);
int					ft_usleep(size_t microseconds);
int					ft_strlen(char *str);
void				print_message(char *str, t_philo *philo, int id);
size_t				get_current_time(void);

#endif
