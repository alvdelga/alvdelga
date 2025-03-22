/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:11:10 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/21 09:11:11 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    pthread_t monitor;

    if (init_data(&data, argc, argv) || init_philos(&data))
        return (printf("Error: Initialization failed\n"), 1);
    pthread_create(&monitor, NULL, monitor_routine, &data);
    for (int i = 0; i < data.num_philos; i++)
        pthread_create(&data.philos[i].thread, NULL, philo_routine, &data.philos[i]);
    for (int i = 0; i < data.num_philos; i++)
        pthread_join(data.philos[i].thread, NULL);
    pthread_join(monitor, NULL);
    free_all(&data);
    return (0);
}
