/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:55:11 by daria             #+#    #+#             */
/*   Updated: 2024/09/24 13:34:57 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	run_simulation(t_state *state)
{
	t_philo		philos[MAX_COUNT];
	pthread_t	philos_threads[MAX_COUNT];

	state->s_start = get_timestamp();
	if (init_mutexes(state, philos))
		return (ERROR);
	if (init_threads(philos, state, philos_threads))
		return (ERROR);
	monitor(philos, state->nb_philos);
	if (destroy_and_exit(philos, philos_threads, state, state->nb_philos))
		return (ERROR);
	return (SUCCESS);
}

int	init_mutexes(t_state *state, t_philo *philos)
{
	int	idx;
	int	nb;

	idx = 0;
	nb = state->nb_philos;
	while (idx < nb)
	{
		if (pthread_mutex_init(&state->forks[idx], NULL))
			return (ERROR);
		if (pthread_mutex_init(&philos[idx].last_meal_mtx, NULL))
			return (ERROR);
		if (pthread_mutex_init(&philos[idx].eaten_times_mutex, NULL))
			return (ERROR);
		idx++;
	}
	if (pthread_mutex_init(&state->print_mtx, NULL)
		|| pthread_mutex_init(&state->exit_mtx, NULL))
		return (ERROR);
	return (SUCCESS);
}

int	init_threads(t_philo *philos, t_state *state, pthread_t *p_threads)
{
	int			idx;
	int			nb;

	idx = 0;
	nb = state->nb_philos;
	while (idx < nb)
	{
		new_philo(&philos[idx], state, idx);
		if (pthread_create(&p_threads[idx], NULL, routine, &philos[idx]))
			return (ERROR);
		idx++;
	}
	return (SUCCESS);
}

int	destroy_and_exit(t_philo *philos, pthread_t *t, t_state *state, int nb)
{
	int	idx;

	idx = 0;
	while (idx < nb)
	{
		if (pthread_join(t[idx], NULL))
			return (ERROR);
		idx++;
	}
	idx = 0;
	while (idx < nb)
	{
		if (pthread_mutex_destroy(&state->forks[idx]))
			return (ERROR);
		if (pthread_mutex_destroy(&philos[idx].last_meal_mtx))
			return (ERROR);
		if (pthread_mutex_destroy(&philos[idx].eaten_times_mutex))
			return (ERROR);
		idx++;
	}
	if (pthread_mutex_destroy(&state->print_mtx)
		|| pthread_mutex_destroy(&state->exit_mtx))
		return (ERROR);
	return (SUCCESS);
}
