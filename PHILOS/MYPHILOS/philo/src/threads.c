/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:21:19 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/28 12:43:16 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	ft_usleep((philo->id % 2) * 5);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;
	int			num_philos;

	i = 0;
	num_philos = program->philos[0].num_of_philos;
	if (pthread_create(&observer, NULL, philo_observer, program->philos) != 0)
		destory_all("Thread creation error", program, forks);
	while (i < num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]) != 0)
			destory_all("Thread creation error", program, forks);
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", program, forks);
	i = 0;
	while (i < num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destory_all("Thread join error", program, forks);
		i++;
	}
	return (0);
}

/*
Main thread (thread_create)
│
├──🧵 pthread_create(observer)        → Empieza el hilo del monitor
├──🧵 pthread_create(philo[0])        → Empieza filósofo 1
├──🧵 pthread_create(philo[1])        → Empieza filósofo 2
├──🧵 ...
│
└──🔒 pthread_join(observer)          → main SE BLOQUEA ESPERANDO
           └── Mientras tanto:
               ├── 🧵 observer da vueltas: "¿Alguien murió?"
               ├── 🧵 filósofo 1 come/piensa/duerme
               ├── 🧵 filósofo 2 también
               └── etc.


*/