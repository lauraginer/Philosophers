/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:42:46 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/22 21:58:23 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

/*tenemos un array de mutex por cada filo en la estructura, aparece como pthread_mutex_t*forks
además de todos los mutex generales*/

int init_philo_mutex(t_data *mutex) //funcion para borrar
{
	main_mutex(&mutex->dead_mutex, mutex, MTX_INIT);
	main_mutex(&mutex->done_mutex, mutex, MTX_INIT);
	main_mutex(&mutex->meal_mutex, mutex, MTX_INIT);
	main_mutex(&mutex->eat_mutex, mutex, MTX_INIT);
	main_mutex(&mutex->log, mutex, MTX_INIT);
}

void	main_mutex(t_philo *forks, t_data *mutex, int action) //inicializa, desbloquea, bloquea para mtx por cada mtx general que pases
{
	int result;
	
	if (action == MTX_INIT)
    {
        result = pthread_mutex_init(mutex, NULL);
        if (result != 0)
            value_state_error(mutex, action);
    }
    else if (action == MTX_LOCK)
    {
        result = pthread_mutex_lock(mutex);
        if (result != 0)
            value_state_error(mutex, action);
    }
    else if (action == MTX_UNLOCK)
    {
        result = pthread_mutex_unlock(mutex);
        if (result != 0)
            value_state_error(mutex, action);
    }
    else if (action == MTX_DESTROY)
    {
        result = pthread_mutex_destroy(mutex);
        if (result != 0)
            value_state_error(mutex, action);
    }
}
void value_state_error(t_data *mutex, int action)
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

// Función para manejar errores y limpiar recursos
void return_error(t_data *data, int error_type)
{
    // Aquí añadirías código para liberar recursos
    // dependiendo del tipo de error
    printf("Error type %d: Exiting program\n", error_type);
    // free_resources(data);
    exit(1);
}