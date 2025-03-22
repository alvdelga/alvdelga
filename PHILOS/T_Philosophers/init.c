/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:11:16 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/21 09:11:18 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        return (printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [max_meals]\n"), 1);
    data->num_philos = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    data->max_meals = (argc == 6) ? atoi(argv[5]) : -1;
    data->someone_died = 0;
    data->start_time = get_time();
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->death_mutex, NULL);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->forks || !data->philos)
        return (1);
    for (int i = 0; i < data->num_philos; i++)
        pthread_mutex_init(&data->forks[i], NULL);
    return (0);
}

int init_philos(t_data *data)
{
    for (int i = 0; i < data->num_philos; i++)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal = get_time();
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].data = data;
    }
    return (0);
}

void free_all(t_data *data)
{
    for (int i = 0; i < data->num_philos; i++)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
    free(data->forks);
    free(data->philos);
}
