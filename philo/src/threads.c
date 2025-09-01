/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:43:12 by lginer-m          #+#    #+#             */
/*   Updated: 2025/09/01 17:27:33 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

/*tenemos un elemento de la estructura, que corresponderia a los hilos,
aparece como pthread_tthread, y además, su posicion según izq o derch,
		pthread_mutex_t	*l_fork
como izquierda y pthread_mutex_t *r_fork* como derecha*/

/*Para los hilos necesitarás:

Inicializar el array de tenedores (data->forks)
Crear los hilos con pthread_create
Implementar la rutina de cada filósofo
Usar pthread_join para esperar a que terminen*/

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
int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (special_case(data)) // si es solo un philo
		return (0);
	data->init_time = obtain_time();
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine_threads,
				(void *)&data->philos[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n", i
				+ 1);
			return (1);
		}
		i++;
	}
	while (!data->dead) // si ningun filo se ha muerto
	{
		monitor_philo(data);
		//usleep(100);
	}
	
	while (i < data->num_philos) // esperar a que todos los hilos terminen
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void	*routine_threads(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg; // puntero a la estructura t_philo
	while (1)               // salimos cuando detectemos muerte
	{
		// Verificar si alguien ha muerto (thread-safe)
		is_dead(philo);
		think(philo);
		is_dead(philo);
		take_forks(philo); // aquí lock de los mutex de los dos forks
		is_dead(philo);
		eat(philo);
		is_dead(philo);
		put_forks(philo); // aquí unlock de los mutex
		is_dead(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void	print_actions(t_data *data, int philo_id, char *log)
{
	long long	current_time;

	current_time = obtain_time() - data->init_time;
	main_mutex(data->log, MTX_LOCK);
	printf("%lld %d %s\n", current_time, philo_id, log);
	main_mutex(data->log, MTX_UNLOCK);
}
