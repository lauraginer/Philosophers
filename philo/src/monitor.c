/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:23:26 by lginer-m          #+#    #+#             */
/*   Updated: 2025/09/03 13:20:13 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int	monitor_philo(t_data *data)
{
	int			i;
	long long	current_time;

	i = 0;
	current_time = obtain_time();
	while (i < data->num_philos)
	{
		main_mutex(&data->eat_mutex, MTX_LOCK);
		if ((current_time - data->philos[i].last_meal) > data->time_die)
		{
			main_mutex(&data->dead_mutex, MTX_LOCK);
			data->dead = 1;
			main_mutex(&data->dead_mutex, MTX_UNLOCK);
			print_actions(data, data->philos[i].id, "died");
			main_mutex(&data->eat_mutex, MTX_UNLOCK);
			return (1);
		}
		main_mutex(&data->eat_mutex, MTX_UNLOCK);
		i++;
	}
	if (manage_all_eaten(data) == 1)
		return (2);
	return (0);
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
