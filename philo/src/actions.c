/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:35 by lauragm           #+#    #+#             */
/*   Updated: 2025/09/02 21:08:58 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void	think(t_philo *philo)
{
	print_actions(philo->data, philo->id, "is thinking");
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		main_mutex(philo->r_fork, MTX_LOCK);
		print_actions(philo->data, philo->id, "has taken a fork");
		main_mutex(philo->l_fork, MTX_LOCK);
		print_actions(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		main_mutex(philo->l_fork, MTX_LOCK);
		print_actions(philo->data, philo->id, "has taken a fork");
		main_mutex(philo->r_fork, MTX_LOCK);
		print_actions(philo->data, philo->id, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	main_mutex(&philo->data->eat_mutex, MTX_LOCK);
	philo->last_meal = obtain_time();
	print_actions(philo->data, philo->id, "is eating");
	if (philo->data->must_eat != -1)
		philo->num_meals++;
	main_mutex(&philo->data->eat_mutex, MTX_UNLOCK);
	time_to_sleep(philo->data->time_eat);
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
