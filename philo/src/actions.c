/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:35 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/27 22:23:45 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	think(t_philo *philo)
{
	// imprimir solo el mensaje, bloqueando y desbloqueando, pensar es solo tiempo de espera
	print_actions(philo->data, philo->id, "is thinking");
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0) // filosofos pares, cogen primero tenedores a su derecha
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

void	put_forks(t_philo *philo)
{
	main_mutex(philo->r_fork, MTX_UNLOCK);
	main_mutex(philo->l_fork, MTX_UNLOCK);
}

void sleep(t_philo *philo)
{
	print_actions(philo->data, philo->id, "is sleeping");
	time_to_sleep(philo->data->time_sleep);
}

void eat(t_philo *philo)
{
	
}
