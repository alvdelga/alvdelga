/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:10:57 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/21 09:10:59 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_data t_data;

typedef struct s_philo
{
    int             id;
    int             meals_eaten;
    long            last_meal;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_data          *data;
}   t_philo;

typedef struct s_data
{
    int             num_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             max_meals;
    long            start_time;
    int             someone_died;
    pthread_mutex_t print_mutex;
    pthread_mutex_t death_mutex;
    pthread_mutex_t *forks;
    t_philo        *philos;
}   t_data;

// utils.c
long    get_time(void);
void    ft_usleep(long time);
void    print_action(t_philo *philo, char *action);

// init.c
int     init_data(t_data *data, int argc, char **argv);
int     init_philos(t_data *data);
void    free_all(t_data *data);

// actions.c
void    *philo_routine(void *arg);

// monitor.c
void    *monitor_routine(void *arg);

#endif
