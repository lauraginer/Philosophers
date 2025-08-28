/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:13:27 by lginer-m          #+#    #+#             */
/*   Updated: 2025/08/28 18:51:52 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define MTX_INIT 0
# define MTX_LOCK 1
# define MTX_UNLOCK 2
# define MTX_DESTROY 3

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int num_philos;              // numero de filosofos
	long long time_die;          // tiempo que tarda en morir
	long long time_eat;          // tiempo que tarda en comer
	long long time_sleep;        // tiempo que tarda en dormir
	int must_eat;                // numero de comidas necesarias
	int dead;                    // comprobacion si alguno muere
	pthread_mutex_t *dead_mutex; // mutex para bloqueo de muerte
	int done;                    // comprobacion si han comido todos
	pthread_mutex_t *done_mutex; // mutex para bloqueo de comidas
	pthread_mutex_t *meal_mutex; // mutex para bloqueo de ultima comida
	pthread_mutex_t *eat_mutex;  // mutex para bloque de si esta comiendo
	long long init_time;         // tiempo de inicio de simulacion
	pthread_mutex_t *log;        // mutex para escribir por pantalla
	pthread_mutex_t *forks;     // array de mutex para usar tenedores (uno por filosofo)
	t_philo *philos;             // estructura para cada filosofo
}t_data;

typedef struct s_philo
{
	int id;                  // id de cada filosofo
	int num_meals;           // numero de comidas
	long long last_meal;     // tiempo de la ultima comida
	int eating;              // comprobacion si esta comiendo
	int meal_done;           // comprobacion si ha hecho todas las comidas
	pthread_t thread;        // hilo asignado (cada filosofo es un hilo)
	pthread_mutex_t *l_fork; // tenedor izquierdo
	pthread_mutex_t *r_fork; // tenedor derecho
	t_data *data;            // estructura de datos general
}t_philo;

// Main functions
int	convert_to_int(const char *str);
int		init_philo(t_data *args);
void	print_values(t_data *args);
int		create_threads(t_data *args);
void	*routine_threads(void *arg);

// Mutex functions
void	init_philo_mutex(t_data *data);
void	main_mutex(pthread_mutex_t *mutex, int action);
void	value_state_error(int action);
void	return_error(t_data *data, int error_type);
void	destroy_mutex(t_data *data);

void	print_actions(t_data *data, int philo_id, char *log);

long long	obtain_time(void);

#endif