/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:23:26 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/29 20:00:06 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

int monitor_philo(t_data *data)
{
	int i;
	long long current_time;
	int finished;

	i = 0;
	current_time = obtain_time();
	while(i < data->num_philos)
	{
		//hay que comprobar el last_meal, este se inicializa en el eat(action)
		//compruebas con el argv y el must_eat, con el mutex del mismo en la variable de must_eat_mutex
	}
}

//comprobar si algún filosofo murió de hambre
//imprimir mensaje de muerte
//comprobar si todos han comido suficiente

/*despues del monitor, hacer el destroy_mutex y liberar todos los mallocs y recursos
de las estructuras y FINNNNNNNNN*/