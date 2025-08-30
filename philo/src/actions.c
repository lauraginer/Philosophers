/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:35 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/30 22:05:22 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	think(t_philo *philo)
{
	// imprimir solo el mensaje, bloqueando y desbloqueando,
		pensar es solo tiempo de espera
	print_actions(philo->data, philo->id, "is thinking");
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0) // filosofos pares,
		cogen primero tenedores a su derecha
	{
		main_mutex(philo->r_fork, MTX_LOCK); // fork derecho
		print_actions(philo->data, philo->id, "has taken a fork");
		main_mutex(philo->l_fork, MTX_LOCK); // fork izquierdo
		print_actions(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		main_mutex(philo->l_fork, MTX_LOCK); // fork izquierdo
		print_actions(philo->data, philo->id, "has taken a fork");
		main_mutex(philo->r_fork, MTX_LOCK); // fork derecho
		print_actions(philo->data, philo->id, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	main_mutex(philo->data->eat_mutex, MTX_LOCK);
		// para asegurarnos de que podemos modificar last_meal
	philo->last_meal = obtain_time();             // actualizarlo
	print_actions(philo->data, philo->id, "is eating");
	if (philo->data->must_eat != -1) // incrementamos conforme vayamos comiendo
		philo->num_meals++;
	main_mutex(philo->data->eat_mutex, MTX_UNLOCK);
	time_to_sleep(philo->data->time_eat);
		// esperamos durante el tiempo de comer
	/*Coger ambos tenedores (bloqueando mutex) ✅
	Actualizar last_meal ✅
	Imprimir acción ✅
	Mantenerse comiendo (precise_sleep(time_to_eat, data)) ✅
	Incrementar contador de comidas (si aplica) ✅
	Soltar tenedores ✅
	Pasar a dormir ✅*/
}

void	put_forks(t_philo *philo)
{
	main_mutex(philo->r_fork, MTX_UNLOCK);
	main_mutex(philo->l_fork, MTX_UNLOCK);
}

void	philo_sleep(t_philo *philo)
{
	print_actions(philo->data, philo->id, "is sleeping");
	time_to_sleep(philo->data->time_sleep);
}
