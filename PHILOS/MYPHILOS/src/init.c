/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:05:40 by druina            #+#    #+#             */
/*   Updated: 2025/03/23 22:05:19 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Initializing the input from user

void	init_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

// Initializing the philosophers

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
	char **argv)
{
	int		i;
	int		num_philos;
	t_philo	*philo;

	i = 0;
	num_philos = ft_atoi(argv[1]);
	while (i < num_philos)
	{
		philo = &philos[i];
		philo->id = i + 1;
		philo->eating = 0;
		philo->meals_eaten = 0;
		init_input(philo, argv);
		philo->start_time = get_current_time();
		philo->last_meal = philo->start_time;
		philo->write_lock = &program->write_lock;
		philo->dead_lock = &program->dead_lock;
		philo->meal_lock = &program->meal_lock;
		philo->dead = &program->dead_flag;
		philo->l_fork = &forks[i];
		philo->r_fork = &forks[(i - 1 + num_philos) % num_philos];
		i++;
	}
}

// Initializing the forks mutexes

int	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i = 0;

	while (i < philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			write(2, "[!] Failed to init fork mutex\n", 31);
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

// Initializing the program structure

int	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (write(2, "[!] Failed to init write_lock\n", 31), 1);
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (write(2, "[!] Failed to init dead_lock\n", 30), 1);
	if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
		return (write(2, "[!] Failed to init meal_lock\n", 30), 1);
	return (0);
}
