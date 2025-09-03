/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:05:54 by lginer-m          #+#    #+#             */
/*   Updated: 2025/09/03 14:08:42 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	init_philo(t_data *args)
{
	int	i;

	i = 0;
	args->philos = malloc(sizeof(t_philo) * args->num_philos);
	if (!args->philos)
	{
		printf("Error: Memory allocation failed for philosophers\n");
		return (-1);
	}
	while (i < args->num_philos)
	{
		args->philos[i].id = i + 1;
		args->philos[i].num_meals = 0;
		args->philos[i].last_meal = obtain_time();
		args->philos[i].eating = 0;
		args->philos[i].meal_done = 0;
		args->philos[i].l_fork = &args->forks[i];
		args->philos[i].r_fork = &args->forks[(i + 1) % args->num_philos];
		main_mutex(&args->forks[i], MTX_INIT);
		args->philos[i].data = args;
		i++;
	}
	return (0);
}

static int	check_args(char **argv, t_data *args)
{
	args->num_philos = convert_to_int(argv[1]);
	args->time_die = convert_to_int(argv[2]);
	args->time_eat = convert_to_int(argv[3]);
	args->time_sleep = convert_to_int(argv[4]);
	if (argv[5])
		args->must_eat = convert_to_int(argv[5]);
	else
		args->must_eat = -1;
	if (args->num_philos == 0 || args->time_die == 0 || args->time_eat == 0
		|| args->time_sleep == 0 || (argv[5] && args->must_eat <= 0))
	{
		printf("Error: invalid value\n");
		return (-1);
	}
	args->dead = 0;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->num_philos);
	if (!args->forks)
	{
		printf("Error: Memory allocation failed for forks\n");
		return (-1);
	}
	return (init_philo(args));
}

int	main(int argc, char **argv)
{
	t_data	args;

	if (argc >= 5 && argc <= 6)
	{
		if (check_args(argv, &args) < 0)
		{
			printf("Error: Failed intent to check args\n");
			return (-1);
		}
		init_philo_mutex(&args);
		if (create_threads(&args) != 0)
			printf("Error: Thread creation failed\n");
		destroy_mutex(&args);
		free_arrays_and_destroy(&args);
	}
	else
		return (-1);
	return (0);
}
