/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:11:46 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/21 09:11:47 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_usleep(long time)
{
    long start = get_time();
    while (get_time() - start < time)
        usleep(100);
}

void print_action(t_philo *philo, char *action)
{
    pthread_mutex_lock(&philo->data->print_mutex);
    if (!philo->data->someone_died)
        printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, action);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
