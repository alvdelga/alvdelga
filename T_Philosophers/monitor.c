/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:11:35 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/21 09:11:37 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;

    while (1)
    {
        for (int i = 0; i < data->num_philos; i++)
        {
            if (get_time() - data->philos[i].last_meal > data->time_to_die)
            {
                print_action(&data->philos[i], "died");
                data->someone_died = 1;
                return (NULL);
            }
        }
        usleep(1000);
    }
}
