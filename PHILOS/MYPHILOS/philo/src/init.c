	/* ************************************************************************** */
	/*                                                                            */
	/*                                                        :::      ::::::::   */
	/*   init.c                                             :+:      :+:    :+:   */
	/*                                                    +:+ +:+         +:+     */
	/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
	/*   Created: 2023/08/09 12:05:40 by druina            #+#    #+#             */
	/*   Updated: 2025/03/24 14:26:01 by alvdelga         ###   ########.fr       */
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

	void	init_philos(t_philo *philoso, t_program *program, pthread_mutex_t *forks,
		char **argv)
	{
		int		i;
		int		num_philos;
		t_philo	*philosofer;

		i = 0;
		num_philos = ft_atoi(argv[1]);
		while (i < num_philos)
		{
			philosofer = &philoso[i];
			philosofer->id = i + 1;
			philosofer->eating = 0;
			philosofer->meals_eaten = 0;
			init_input(philosofer, argv);
			philosofer->start_time = get_current_time();
			philosofer->last_meal = philosofer->start_time;
			philosofer->write_lock = &program->write_lock;
			philosofer->dead_lock = &program->dead_lock;
			philosofer->meal_lock = &program->meal_lock;
			philosofer->dead = &program->dead_flag;
			philosofer->l_fork = &forks[i];
			philosofer->r_fork = &forks[(i - 1 + num_philos) % num_philos];
			i++;
		}
	}

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


	int	init_program(t_program *program, t_philo *philosofer)
	{
		program->dead_flag = 0;
		program->philos = philosofer;
		if (pthread_mutex_init(&program->write_lock, NULL) != 0)
			return (write(2, "[!] Failed to init write_lock\n", 31), 1);
		if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
			return (write(2, "[!] Failed to init dead_lock\n", 30), 1);
		if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
			return (write(2, "[!] Failed to init meal_lock\n", 30), 1);
		return (0);
	}
