/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:21:19 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/27 12:11:15 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Checks if the value of dead_flag changed

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

// Thread routine

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(10);
	// if (philo->num_of_philos % 2 == 0)
	// 	ft_usleep(10);
	ft_usleep((philo->id % 2) * 5);
	// ft_usleep((philo->id % 2) * (philo->time_to_eat * 0.9 + 1));
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
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

	// Crear hilo observador (monitor de muerte/comidas)
	if (pthread_create(&observer, NULL, philo_observer, program->philos) != 0)
		destory_all("Thread creation error", program, forks);

	// Crear hilos de los filósofos
	while (i < num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine, &program->philos[i]) != 0)
			destory_all("Thread creation error", program, forks);
		i++;
	}

	// Esperar a que termine el observador
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", program, forks);

	// Esperar a que terminen todos los filósofos
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
🧩 Orden real de eventos:
🧠 El observer se crea y empieza a ejecutar en paralelo.

🍝 Inmediatamente después, se crean los hilos de los filósofos con pthread_create(...).

🔁 Cada filósofo empieza su rutina (philo_routine) en paralelo: comer, dormir, pensar.

🧍 El main thread solo espera al observer con pthread_join, pero eso no impide que los filósofos ya estén activos.

✅ Todo esto ocurre en paralelo, gracias al sistema de hilos POSIX.

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