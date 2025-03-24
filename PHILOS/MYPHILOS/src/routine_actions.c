/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:20:53 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/24 12:30:48 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Think routine funtion

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
	// ft_usleep(5);
}

// Dream routine funtion

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}


int take_forks(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t **second)
{
	if (philo->l_fork < philo->r_fork)
	{
		*first = philo->l_fork;
		*second = philo->r_fork;
	}
	else
	{
		*first = philo->r_fork;
		*second = philo->l_fork;
	}
	pthread_mutex_lock(*first);
	print_message("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(*first);
		return (0); // no puede comer
	}
	pthread_mutex_lock(*second);
	print_message("has taken a fork", philo, philo->id);
	return (1); // puede proceder a comer
}

void eat(t_philo *philo)
{
	pthread_mutex_t *first;
	pthread_mutex_t *second;

	if (!take_forks(philo, &first, &second))
		return ;

	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->time_to_eat);
	
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

