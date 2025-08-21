/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:42:46 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/21 20:09:00 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

/*tenemos un array de mutex por cada filo en la estructura, aparece como pthread_mutex_t*forks
además de todos los mutex generales*/

int init_philo_mutex(t_data *mutex) //funcion para borrar
{
	pthread_mutex_init(&mutex->dead_mutex, NULL);
	pthread_mutex_init(&mutex->done_mutex, NULL);
	pthread_mutex_init(&mutex->meal_mutex, NULL);
	pthread_mutex_init(&mutex->eat_mutex, NULL);
	pthread_mutex_init(&mutex->_mutex, NULL); 
}

void	main_mutex(t_table *table, t_mtx *mutex) //inicializa, desbloquea, bloquea para mtx por cada mtx general que pases
{
	int action;
	
	action = 0;
	if (action == MTX_INIT && pthread_mutex_init(mutex, NULL))
	{
		value_state_error(action); //dependiendo del valor que de la operacion, si es falsa, imprime el error
		exit_error(table, MTX_INIT);
	}
	if (action == MTX_LOCK && pthread_mutex_lock(mutex))
	{
		value_state_error(action);
		exit_error(table, MTX_LOCK);
	}	
	if (action == MTX_UNLOCK && pthread_mutex_unlock(mutex))
	{
		value_state_error(action);
		exit_error(table, MTX_UNLOCK);
	}
	if (action == MTX_DESTROY && pthread_mutex_destroy(mutex))
	{
		value_state_error(action);
		exit_error(table, MTX_DESTROY);
	}
}
void value_state_error(int action)
{	
	if(action == 1)
		printf("Error: Failed main mutex\n")
}