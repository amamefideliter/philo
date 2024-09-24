/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:41:11 by dzubkova          #+#    #+#             */
/*   Updated: 2024/09/24 13:34:17 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "../libft/libft.h"

# define ERROR 1
# define SUCCESS 0
# define NOT_SET -1

# define MAX_COUNT 200

# define EAT "is eating!"
# define SLEEP "is sleeping!"
# define THINK "is thinking!"
# define DIE "died!"
# define FORK "has taken a fork!"

# define DIED 1
# define EXIT 1

typedef long long	t_milliseconds;

typedef struct s_state
{
	t_milliseconds	s_start;
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;
	int				nb_philos;
	int				meal_count;

	pthread_mutex_t	forks[MAX_COUNT];
	pthread_mutex_t	print_mtx;

	pthread_mutex_t	exit_mtx;
	int				exit;
}	t_state;

typedef struct s_philo
{
	int				idx;
	int				eaten_times;
	pthread_mutex_t	eaten_times_mutex;
	pthread_mutex_t	last_meal_mtx;
	t_milliseconds	last_meal;
	t_state			*state;
}	t_philo;

int		get_timestamp(void);
int		run_simulation(t_state *state);
int		init_mutexes(t_state *state, t_philo *philos);
int		init_threads(t_philo *philos, t_state *state, pthread_t *p_threads);
int		think(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		eat(t_philo *philo);
int		check_death(t_philo *philo);
int		monitor(t_philo *philos, int nb);
int		is_somebody_dead(t_philo *philo);
int		destroy_and_exit(t_philo *philos, pthread_t *t, t_state *state, int nb);
void	*routine(void *philo_void);
void	check_meal_count(t_philo *philo, int *all_eaten);
void	message(char *action, t_philo *philo);
void	print_message(char *action, t_philo *philo);
void	new_philo(t_philo *philo, t_state *state, int idx);

#endif