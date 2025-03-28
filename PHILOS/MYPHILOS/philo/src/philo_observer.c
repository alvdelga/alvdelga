/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_observer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:20:25 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/28 21:12:10 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_dead(t_philo *philos)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = philos[0].num_of_philos;
	while (i < num_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			print_message(RED "died" RESET, &philos[i], philos[i].id);
			pthread_mutex_lock(philos[i].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Checks if all the philos ate the num_of_meals

int	check_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;
	int	num_philos;

	i = 0;
	finished_eating = 0;
	num_philos = philos[0].num_of_philos;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < num_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == num_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*philo_observer(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_dead(philos) == 1 || check_all_ate(philos) == 1)
			break ;
	return (pointer);
}
