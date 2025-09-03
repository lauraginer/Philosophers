/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:43:12 by lginer-m          #+#    #+#             */
/*   Updated: 2025/09/03 14:16:21 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

static int	special_case(t_data *data)
{
	if (data->num_philos == 1)
	{
		print_actions(data, data->philos[0].id, "has taken a fork");
		time_to_sleep(data->time_die);
		print_actions(data, data->philos[0].id, "is dead");
		return (1);
	}
	return (0);
}

static int	dead_and_need_put_forks(t_philo *philo)
{
	if (is_dead(philo) == 1)
	{
		put_forks(philo);
		return (1);
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (special_case(data))
		return (0);
	data->init_time = obtain_time();
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine_threads,
				(void *)&data->philos[i]) != 0)
		{
			printf("Error: Failed to create thread %d\n", i + 1);
			return (1);
		}
		i++;
	}
	while (!data->dead)
	{
		if (monitor_philo(data))
			break ;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void	*routine_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (is_dead(philo) == 1)
			return (NULL);
		think(philo);
		if (is_dead(philo) == 1)
			return (NULL);
		take_forks(philo);
		if (dead_and_need_put_forks(philo) == 1)
			return (NULL);
		eat(philo);
		if (dead_and_need_put_forks(philo) == 1)
			return (NULL);
		put_forks(philo);
		if (is_dead(philo) == 1)
			return (NULL);
		philo_sleep(philo);
	}
	return (NULL);
}

void	print_actions(t_data *data, int philo_id, char *log)
{
	long long	current_time;

	current_time = obtain_time() - data->init_time;
	main_mutex(&data->log, MTX_LOCK);
	printf("%lld %d %s\n", current_time, philo_id, log);
	main_mutex(&data->log, MTX_UNLOCK);
}
