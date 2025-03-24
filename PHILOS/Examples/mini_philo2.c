/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_philo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 08:09:40 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/24 08:19:46 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#define N 5 // número de filósofos

typedef struct {
	int id;
	pthread_mutex_t *tenedor_izq;
	pthread_mutex_t *tenedor_der;
	int time_to_eat;
} Filosofo;

double timestamp_s() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_usec / 1000000.0);
}

void *rutina_filosofo(void *arg) {
	Filosofo *f = (Filosofo *)arg;

	printf("%.3f Filósofo %d está pensando\n", timestamp_s(), f->id);
	usleep(500 * 1000);

    if (f->id % 2 == 0) {
        pthread_mutex_lock(f->tenedor_der);
        pthread_mutex_lock(f->tenedor_izq);
    } else {
        pthread_mutex_lock(f->tenedor_izq);
        pthread_mutex_lock(f->tenedor_der);
    }
    

	printf("%.3f Filósofo %d está comiendo\n", timestamp_s(), f->id);
	usleep(f->time_to_eat * 1000);

	pthread_mutex_unlock(f->tenedor_der);
	pthread_mutex_unlock(f->tenedor_izq);
	printf("%.3f Filósofo %d terminó de comer y soltó los tenedores\n", timestamp_s(), f->id);

	printf("%.3f Filósofo %d está durmiendo\n", timestamp_s(), f->id);
	usleep(500 * 1000);

	printf("%.3f Filósofo %d terminó su rutina\n", timestamp_s(), f->id);
	return NULL;
}

int main() {
	pthread_t hilos[N];
	Filosofo filosofos[N];
	pthread_mutex_t tenedores[N];
	int i;
    
	// Inicializar mutexes (tenedores)
	i = 0;
	while (i < N) {
		pthread_mutex_init(&tenedores[i], NULL);
		i++;
	}

	// Inicializar filósofos y crear hilos
	i = 0;
	while (i < N) {
		filosofos[i].id = i + 1;
		filosofos[i].tenedor_izq = &tenedores[i];
		filosofos[i].tenedor_der = &tenedores[(i + 1) % N]; // circular
		filosofos[i].time_to_eat = 1000;

		pthread_create(&hilos[i], NULL, rutina_filosofo, &filosofos[i]);
		i++;
	}

	// Esperar a que terminen los hilos
	i = 0;
	while (i < N) {
		pthread_join(hilos[i], NULL);
		i++;
	}

	// Destruir mutexes
	i = 0;
	while (i < N) {
		pthread_mutex_destroy(&tenedores[i]);
		i++;
	}
    

	return 0;
}
