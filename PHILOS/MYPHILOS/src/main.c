/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:23:28 by druina            #+#    #+#             */
/*   Updated: 2025/03/26 09:51:12 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

// Checks that the input is only numbers

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_valid_args(char **argv)
{
    int num_philo = ft_atoi(argv[1]);
    int time_to_die = ft_atoi(argv[2]);
    int time_to_eat = ft_atoi(argv[3]);
    int time_to_sleep = ft_atoi(argv[4]);
    // int num_to_eats = ft_atoi(argv[5]);
    
	if (num_philo > MAX_PHILO || num_philo <= 0
		|| check_arg_content(argv[1]) == 1)
	return (write(2, "\033[31m[!]\033[0m Invalid philosophers\n", 35), -1);
	if (time_to_die <= 0 || check_arg_content(argv[2]) == -1)
		return (write(2, "\033[31m[!]\033[0m Invalid time to die\n", 34), -1);
	if (time_to_eat <= 0 || check_arg_content(argv[3]) == -1)
		return (write(2, "\033[31m[!]\033[0m Invalid time to eat\n", 34), -1);
	if (time_to_sleep <= 0 || check_arg_content(argv[4]) == -1)
		return (write(2, "\033[31m[!]\033[0m Invalid time to sleep\n", 36), -1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_content(argv[5]) == 1))
		return (write(2, "\033[31m[!]\033[0m Invalid number of times\n", 38), -1);

	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philosofer[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];

	if (argc != 5 && argc != 6)
		return (write(2, "\033[31m[!]\033[0m Wrong arguments\n", 30), 1);

	if (check_valid_args(argv) == -1)
		return (1);
    if (init_program(&program, philosofer) != 0)
        return (1);
    if (init_forks(forks, ft_atoi(argv[1])) != 0)
		return (1);

	init_philos(philosofer, &program, forks, argv);
	thread_create(&program, forks);
	destory_all(NULL, &program, forks);
	return (0);
}
