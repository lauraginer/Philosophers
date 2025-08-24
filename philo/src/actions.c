/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauragm <lauragm@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 19:00:35 by lauragm           #+#    #+#             */
/*   Updated: 2025/08/24 19:17:10 by lauragm          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

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