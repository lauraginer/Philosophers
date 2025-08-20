/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:39:59 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/20 21:32:10 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int convert_to_int(const char *str)
{
	int	i;
	int	sign;
	long res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return(-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if(res >= INT_MAX)
			return(INT_MAX);
	}
	return (sign * res);
}
void print_values(t_data *args)
{
    int i;

    printf("\n--------- DATOS GENERALES ---------\n");
    printf("Número de filósofos: %d\n", args->num_philos);
    printf("Tiempo para morir: %lld ms\n", args->time_die);
    printf("Tiempo para comer: %lld ms\n", args->time_eat);
    printf("Tiempo para dormir: %lld ms\n", args->time_sleep);
    
    if (args->must_eat == -1)
        printf("Comidas necesarias: Infinitas\n");
    else
        printf("Comidas necesarias: %d\n", args->must_eat);
    
    printf("\n--------- DATOS DE FILÓSOFOS ---------\n");
    i = 0;
    while (i < args->num_philos)
    {
        printf("\nFilósofo %d:\n", args->philos[i].id);
        printf("  Comidas realizadas: %d\n", args->philos[i].num_meals);
        printf("  Última comida (tiempo): %lld\n", args->philos[i].last_meal);
        printf("  Estado comiendo: %s\n", args->philos[i].eating ? "Sí" : "No");
        printf("  Comidas completadas: %s\n", args->philos[i].meal_done ? "Sí" : "No");
        printf("  Dirección de memoria de datos: %p\n", (void*)args->philos[i].data);
        i++;
    }
    printf("\n------------------------------------\n");
}
