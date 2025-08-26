/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:35 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/26 19:48:14 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

void think(t_philo *philo)
{
	//imprimir solo el mensaje, bloqueando y desbloqueando, pensar es solo tiempo de espera
	print_actions(philo->data, philo->id, "is thinking");
}

void take_forks(t_philo *philo)
{
	if(philo->id % 2 == 0) //filosofos pares, cogen primero tenedores a su derecha
	{
		main_mutex(philo->data->r_fork, MTX_LOCK); // fork derecho
		print_actions(philo->data, philo->id, "has taken a fork");
		main_mutex(philo->data->l_fork, MTX_LOCK); // fork izquierdo
		print_actions(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		main_mutex(philo->data->l_fork, MTX_UNLOCK); //fork izquierdo
		print_actions(philo->data, philo->id, "has taken a fork");
		main_mutex(philo->data->r_fork, MTX_UNLOCK);
		print_actions(philo->data, philo->id, "has taken a fork");
	}
}
	
void put_forks(t_philo *philo)
{
	
}

Resumen de mutex por propósito:
🍴 Tenedores (l_fork, r_fork):
LOCK: Antes de comer (tomar tenedores)
UNLOCK: Después de comer (soltar tenedores)
Evita: Que dos filósofos usen el mismo tenedor

📝 Log (log):
LOCK/UNLOCK: Cada vez que imprimes algo
Evita: Que los mensajes se mezclen en la salida

💀 Muerte (dead_mutex):
LOCK/UNLOCK: Al leer/escribir data->dead
Evita: Race conditions al detectar muerte

🍽️ Comida (meal_mutex):
LOCK/UNLOCK: Al actualizar last_meal, num_meals
Evita: Race conditions en datos de comida

😋 Estado comiendo (eat_mutex):
LOCK/UNLOCK: Al cambiar eating (true/false)
Evita: Race conditions en el estado

⚠️ Puntos críticos para evitar deadlock:
Orden de tenedores: Filósofos pares e impares toman tenedores en orden diferente
Tiempo de bloqueo: Mantener los locks el mínimo tiempo posible
Un filósofo solo: Caso especial (no puede comer nunca)