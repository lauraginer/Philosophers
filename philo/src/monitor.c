/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:23:26 by lginer-m          #+#    #+#             */
/*   Updated: 2025/09/01 17:19:02 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void monitor_philo(t_data *data)
{
	int i;
	long long current_time;

	i = 0;
	current_time = obtain_time();
	while(i < data->num_philos)
	{
		main_mutex(data->eat_mutex, MTX_LOCK); //comprobar si algún filosofo murió de hambre
		//printf("Valor de antes: %lld\n", current_time - data->philos[i].last_meal);
		//printf("Time die: %lld\n", data->time_die);
		if((current_time - data->philos[i].last_meal) > data->time_die)
		{
			main_mutex(data->dead_mutex, MTX_LOCK);
			data->dead = 1; //señal de muerte
			main_mutex(data->dead_mutex, MTX_UNLOCK);
			print_actions(data, data->philos[i].id, "died");
			main_mutex(data->eat_mutex, MTX_UNLOCK);
			return;
		}
		main_mutex(data->eat_mutex, MTX_UNLOCK);
		i++;
	}
	manage_all_eaten(data);
	return;
}

void manage_all_eaten(t_data *data) //comprobar si todos han comido suficiente
{
	int finished;
	int i;

	if(data->must_eat != -1) //verificamos si existe el argv5
	{
		i = 0;
		finished = 1; //asumimos que han terminado de primeras
		while(i < data->num_philos)
		{
			main_mutex(data->eat_mutex, MTX_LOCK);
			if(data->philos[i].num_meals < data->must_eat)
				finished = 0;
			main_mutex(data->eat_mutex, MTX_UNLOCK);
			i++;
		}
		if(finished)
		{
			main_mutex(data->dead_mutex, MTX_LOCK);
			data->dead = 1; //se terminacion la simulacion pero no se mueren
			main_mutex(data->dead_mutex, MTX_UNLOCK);
			return; //todos han comido
		}
	}
	return;
}

