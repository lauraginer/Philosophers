/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:42:46 by lginer-m          #+#    #+#             */
/*   Updated: 2025/09/02 21:12:29 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

/*tenemos un array de mutex por cada filo en la estructura,
aparece como pthread_mutex_t*forks además de todos los mutex generales*/

void	init_philo_mutex(t_data *data)
{
	main_mutex(&data->dead_mutex, MTX_INIT);
	main_mutex(&data->done_mutex, MTX_INIT);
	main_mutex(&data->meal_mutex, MTX_INIT);
	main_mutex(&data->eat_mutex, MTX_INIT);
	main_mutex(&data->log, MTX_INIT);
}

void	main_mutex(pthread_mutex_t *mutex, int action)
{
	int result;

	if (action == MTX_INIT)
	{
		result = pthread_mutex_init(mutex, NULL);
		if (result == -1)
			value_state_error(action);
	}
	else if (action == MTX_LOCK)
	{
		result = pthread_mutex_lock(mutex);
		if (result == -1)
			value_state_error(action);
	}
	else if (action == MTX_UNLOCK)
	{
		result = pthread_mutex_unlock(mutex);
		if (result == -1)
			value_state_error(action);
	}
	else if (action == MTX_DESTROY)
	{
		result = pthread_mutex_destroy(mutex);
		if (result == -1)
			value_state_error(action);
	}
}

void	value_state_error(int action)
{
	if (action == MTX_INIT)
	{
		printf("Error: Failed to initialize mutex\n");
		return ;
	}
	if (action == MTX_LOCK)
	{
		printf("Error: Failed to lock mutex\n");
		return ;
	}
	if (action == MTX_UNLOCK)
	{
		printf("Error: Failed to unlock mutex\n");
		return ;
	}
	if (action == MTX_DESTROY)
	{
		printf("Error: Failed to destroy mutex\n");
		return ;
	}
}

void	destroy_mutex(t_data *data)
{
	main_mutex(&data->meal_mutex, MTX_DESTROY);
	main_mutex(&data->eat_mutex, MTX_DESTROY);
	main_mutex(&data->log, MTX_DESTROY);
	return ;
}

void	free_arrays_and_destroy(t_data *data)
{
	int	i;
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			main_mutex(&data->forks[i], MTX_DESTROY);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
	}
		main_mutex(&data->dead_mutex, MTX_DESTROY);
		main_mutex(&data->done_mutex, MTX_DESTROY);
}
