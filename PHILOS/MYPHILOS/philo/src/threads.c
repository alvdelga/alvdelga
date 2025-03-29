/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:20:06 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/29 20:03:50 by alvdelga         ###   ########.fr       */
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

	// Esperar a que el monitor esté listo
	pthread_mutex_lock(&philo->progra->monitor_lock);
	while (!philo->progra->monitor_ready)
	{
		pthread_mutex_unlock(&philo->progra->monitor_lock);
		usleep(50);
		pthread_mutex_lock(&philo->progra->monitor_lock);
	}
	pthread_mutex_unlock(&philo->progra->monitor_lock);

	ft_usleep((philo->id % 2) * 5);

	while (!dead_loop(philo))
	{
		eat(philo);
		ft_sleep(philo);
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
Tiempo         | Hilo Filósofo                   | Hilo Monitor
---------------|-------------------------|-------------------------------
T = 1000 ms    | intenta lock(meal_lock)         | -
               | consigue el lock                | -
               | eating = 1                      | -
               | last_meal = 1000                | -
               | meals_eaten++                   | -
               | unlock(meal_lock)               | -

T = 1001 ms    | ft_usleep(time_to_eat = 200)    | intenta lock(meal_lock)
               | (durmiendo)                     | consigue el lock
               |                         | get_current_time() - last_meal = 1
               |                                 | eating == 1 → NO ha muerto
               |                                 | unlock(meal_lock)

T = 1201 ms    | despierta del ft_usleep         | -
               | intenta lock(meal_lock)         | -
               | consigue el lock                | -
               | eating = 0                      | -
               | unlock(meal_lock)               | -

T = 1202 ms    | sigue con rutina                | intenta lock(meal_lock)
               |                                 | consigue el lock
               |                     | get_current_time() - last_meal = 202
               |                                 | eating == 0 → ¿ha muerto?
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