/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:08:44 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/21 11:21:03 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct {
    int id;
    pthread_mutex_t *tenedor_izq;
    pthread_mutex_t *tenedor_der;
    int time_to_eat;
} Filosofo;

double timestamp_s() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

void *rutina_filosofo(void *arg) {
    Filosofo *f = (Filosofo *)arg;

    printf("%.3f Filósofo %d está pensando\n", timestamp_s(), f->id);
    usleep(500 * 1000);  // piensa medio segundo

    pthread_mutex_lock(f->tenedor_izq);
    printf("%.3f Filósofo %d tomó el tenedor izquierdo\n", timestamp_s(), f->id);

    pthread_mutex_lock(f->tenedor_der);
    printf("%.3f Filósofo %d tomó el tenedor derecho\n", timestamp_s(), f->id);

    printf("%.3f Filósofo %d está comiendo\n", timestamp_s(), f->id);
    usleep(f->time_to_eat * 1000);  // come durante time_to_eat ms

    pthread_mutex_unlock(f->tenedor_der);
    pthread_mutex_unlock(f->tenedor_izq);
    printf("%.3f Filósofo %d terminó de comer y soltó los tenedores\n", timestamp_s(), f->id);

    printf("%.3f Filósofo %d está durmiendo\n", timestamp_s(), f->id);
    usleep(500 * 1000);  // duerme medio segundo

    printf("%.3f Filósofo %d terminó su rutina\n", timestamp_s(), f->id);

    return NULL;
}


int main() {
    pthread_t hilo1, hilo2;
    pthread_mutex_t tenedor_1 = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t tenedor_2 = PTHREAD_MUTEX_INITIALIZER;

    Filosofo f1 = {
        .id = 1,
        .tenedor_izq = &tenedor_1,
        .tenedor_der = &tenedor_2,
        .time_to_eat = 1000
    };
    
    Filosofo f2 = {
        .id = 2,
        .tenedor_izq = &tenedor_1,
        .tenedor_der = &tenedor_2,
        .time_to_eat = 1000
    };

    pthread_create(&hilo1, NULL, rutina_filosofo, &f1);
    pthread_create(&hilo2, NULL, rutina_filosofo, &f2);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    pthread_mutex_destroy(&tenedor_1);
    pthread_mutex_destroy(&tenedor_2);
    
    return 0;
}
