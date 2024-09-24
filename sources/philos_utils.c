/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:59:27 by daria             #+#    #+#             */
/*   Updated: 2024/09/24 13:33:39 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	new_philo(t_philo *philo, t_state *state, int idx)
{
	philo->idx = idx;
	philo->state = state;
	philo->last_meal = state->s_start;
	philo->eaten_times = 0;
}

void	message(char *action, t_philo *philo)
{
	printf("%5lld ", get_timestamp() - philo->state->s_start);
	printf("%d %s\n", philo->idx + 1, action);
}

void	print_message(char *action, t_philo *philo)
{
	pthread_mutex_lock(&philo->state->print_mtx);
	message(action, philo);
	pthread_mutex_unlock(&philo->state->print_mtx);
}

int	is_somebody_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->exit_mtx);
	if (philo->state->exit == EXIT)
	{
		pthread_mutex_unlock(&philo->state->exit_mtx);
		return (EXIT);
	}
	pthread_mutex_unlock(&philo->state->exit_mtx);
	return (SUCCESS);
}
