/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:23:26 by lginer-m          #+#    #+#             */
/*   Updated: 2025/09/03 20:02:59 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	check_philo_death(t_data *data, int i, long long current_time)
{
	main_mutex(&data->eat_mutex, MTX_LOCK);
	if ((current_time - data->philos[i].last_meal) > data->time_die)
	{
		main_mutex(&data->dead_mutex, MTX_LOCK);
		data->dead = 1;
		main_mutex(&data->dead_mutex, MTX_UNLOCK);
		main_mutex(&data->log, MTX_LOCK);
		printf("%lld %d died\n", current_time - data->init_time,
			data->philos[i].id);
		main_mutex(&data->log, MTX_UNLOCK);
		main_mutex(&data->eat_mutex, MTX_UNLOCK);
		return (1);
	}
	main_mutex(&data->eat_mutex, MTX_UNLOCK);
	return (0);
}

void	*monitor_philo(void *arg)
{
	t_data		*data;
	int			i;
	long long	current_time;

	data = (t_data *)arg;
	while (!data->dead)
	{
		i = 0;
		current_time = obtain_time();
		while (i < data->num_philos && !data->dead)
		{
			if (check_philo_death(data, i, current_time))
				return (NULL);
			i++;
		}
		if (manage_all_eaten(data) == 1)
		{
			print_actions(data, 0, "All philosophers have eaten enough!");
			return (NULL);
		}
	}
	return (NULL);
}

int	manage_all_eaten(t_data *data)
{
	int	finished;
	int	i;

	if (data->must_eat != -1)
	{
		i = 0;
		finished = 1;
		while (i < data->num_philos)
		{
			main_mutex(&data->eat_mutex, MTX_LOCK);
			if (data->philos[i].num_meals < data->must_eat)
				finished = 0;
			main_mutex(&data->eat_mutex, MTX_UNLOCK);
			i++;
		}
		if (finished)
		{
			main_mutex(&data->dead_mutex, MTX_LOCK);
			data->dead = 1;
			main_mutex(&data->dead_mutex, MTX_UNLOCK);
			return (1);
		}
	}
	return (0);
}

void	join_threads(int i, pthread_t monitor_thread, t_data *data)
{
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}
