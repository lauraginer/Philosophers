/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lginer-m <lginer-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:13:27 by lginer-m          #+#    #+#             */
/*   Updated: 2025/09/03 20:03:04 by lginer-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MTX_INIT 0
# define MTX_LOCK 1
# define MTX_UNLOCK 2
# define MTX_DESTROY 3

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philos;		/* Number of philosophers */
	long long		time_die;		/* Time until a philosopher dies (in ms) */
	long long		time_eat;		/* Time it takes to eat (in ms) */
	long long		time_sleep;		/* Time it takes to sleep (in ms) */
	int				must_eat;		/* Number of meals required */
	int				dead;			/* Flag to check if any philosopher died */
	pthread_mutex_t	dead_mutex;		/* Mutex for death flag access */
	pthread_mutex_t	done_mutex;		/* Mutex for done flag access */
	pthread_mutex_t	meal_mutex;		/* Mutex for last meal timing access */
	pthread_mutex_t	eat_mutex;		/* Mutex for eating state access */
	long long		init_time;		/* Simulation start time */
	pthread_mutex_t	log;			/* Mutex for console output */
	pthread_mutex_t	*forks;			/* Array of mutexes for forks */
	t_philo			*philos;		/* Array of philosopher structures */
}	t_data;

typedef struct s_philo
{
	int				id;				/* Philosopher ID */
	int				num_meals;		/* Number of meals eaten */
	long long		last_meal;		/* Timestamp of the last meal */
	int				eating;			/* Flag to check if philosopher is eating */
	int				meal_done;		/* Flag to check if all has eaten enough */
	pthread_t		thread;			/* Thread assigned to philosopher */
	pthread_mutex_t	*l_fork;		/* Left fork */
	pthread_mutex_t	*r_fork;		/* Right fork */
	t_data			*data;			/* Pointer to general data structure */
}	t_philo;

/* Main functions */
int			init_philo(t_data *args);

/* Mutex functions */
void		init_philo_mutex(t_data *data);
void		main_mutex(pthread_mutex_t *mutex, int action);
void		value_state_error(int action);
void		destroy_mutex(t_data *data);
void		free_arrays_and_destroy(t_data *data);

/* Monitor functions */
void		*monitor_philo(void *arg);
int			manage_all_eaten(t_data *data);
int			check_philo_death(t_data *data, int i, long long current_time);
void		join_threads(int i, pthread_t	monitor_thread, t_data *data);

/* Threads functions */
int			create_threads(t_data *args);
void		*routine_threads(void *arg);
void		print_actions(t_data *data, int philo_id, char *log);

/* Utils functions */
int			convert_to_int(const char *str);
void		print_values(t_data *args);
long long	obtain_time(void);
int			time_to_sleep(long long duration);
int			is_dead(t_philo *philo);

/* Actions functions */
void		think(t_philo *philo);
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		put_forks(t_philo *philo);
void		philo_sleep(t_philo *philo);
#endif /* PHILOSOPHER_H */