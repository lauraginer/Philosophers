/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:42:46 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/24 16:23:38 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

/*tenemos un array de mutex por cada filo en la estructura, aparece como pthread_mutex_t*forks
además de todos los mutex generales*/

void init_philo_mutex(t_data *data)
{
	data->dead_mutex = malloc(sizeof(pthread_mutex_t));
	data->done_mutex = malloc(sizeof(pthread_mutex_t));
	data->meal_mutex = malloc(sizeof(pthread_mutex_t));
	data->eat_mutex = malloc(sizeof(pthread_mutex_t));
	data->log = malloc(sizeof(pthread_mutex_t));
	
	if (!data->dead_mutex || !data->done_mutex || !data->meal_mutex || 
		!data->eat_mutex || !data->log)
	{
		printf("Error: Failed to allocate memory for mutex\n");
		return;
	}
	main_mutex(data->dead_mutex, MTX_INIT);
	main_mutex(data->done_mutex, MTX_INIT);
	main_mutex(data->meal_mutex, MTX_INIT);
	main_mutex(data->eat_mutex, MTX_INIT);
	main_mutex(data->log, MTX_INIT);
}

void	main_mutex(pthread_mutex_t *mutex, int action) //inicializa, desbloquea, bloquea para mtx por cada mtx general que pases
{
	int result;
	
	if (action == MTX_INIT)
    {
        result = pthread_mutex_init(mutex, NULL);
        if (result != 0)
            value_state_error(action);
    }
    else if (action == MTX_LOCK)
    {
        result = pthread_mutex_lock(mutex);
		if (result != 0)
            value_state_error(action);
    }
    else if (action == MTX_UNLOCK)
    {
        result = pthread_mutex_unlock(mutex);
		if (result != 0)
            value_state_error(action);
    }
    else if (action == MTX_DESTROY)
    {
        result = pthread_mutex_destroy(mutex);
		if (result != 0)
            value_state_error(action);
    }
}

void value_state_error(int action)
{	
	if (action == MTX_INIT)
		printf("Error: Failed to initialize mutex\n");
	if (action == MTX_LOCK)
		printf("Error: Failed to lock mutex\n");
	if (action == MTX_UNLOCK)
		printf("Error: Failed to unlock mutex\n");
	if (action == MTX_DESTROY)
		printf("Error: Failed to destroy mutex\n");
}

void destroy_mutex(t_data *data) // liberar memoria de mutex(no estoy segura de si esta funcion es necesaria)
{
	if (data->dead_mutex)
	{
		main_mutex(data->dead_mutex, MTX_DESTROY);
		free(data->dead_mutex);
	}
	if (data->done_mutex)
	{
		main_mutex(data->done_mutex, MTX_DESTROY);
		free(data->done_mutex);
	}
	if (data->meal_mutex)
	{
		main_mutex(data->meal_mutex, MTX_DESTROY);
		free(data->meal_mutex);
	}
	if (data->eat_mutex)
	{
		main_mutex(data->eat_mutex, MTX_DESTROY);
		free(data->eat_mutex);
	}
	if (data->log)
	{
		main_mutex(data->log, MTX_DESTROY);
		free(data->log);
	}
}