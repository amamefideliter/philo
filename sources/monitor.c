/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:12:18 by daria             #+#    #+#             */
/*   Updated: 2024/09/24 13:33:33 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

int	monitor(t_philo *philos, int nb)
{
	int	idx;
	int	all_eaten;

	while (1)
	{
		idx = 0;
		all_eaten = 1;
		while (idx < nb)
		{
			if (check_death(&philos[idx]))
			{
				print_message(DIE, &philos[idx]);
				return (EXIT);
			}
			check_meal_count(&philos[idx++], &all_eaten);
		}
		if (all_eaten)
		{
			pthread_mutex_lock(&philos->state->exit_mtx);
			philos->state->exit = EXIT;
			pthread_mutex_unlock(&philos->state->exit_mtx);
			return (EXIT);
		}
	}
	return (SUCCESS);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	if (get_timestamp() - philo->last_meal > philo->state->time_to_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mtx);
		pthread_mutex_lock(&philo->state->exit_mtx);
		philo->state->exit = EXIT;
		pthread_mutex_unlock(&philo->state->exit_mtx);
		return (DIED);
	}
	pthread_mutex_unlock(&philo->last_meal_mtx);
	return (SUCCESS);
}

void	check_meal_count(t_philo *philo, int *all_eaten)
{
	pthread_mutex_lock(&philo->eaten_times_mutex);
	if (philo->eaten_times < philo->state->meal_count
		|| philo->state->meal_count == NOT_SET)
		*all_eaten = 0;
	pthread_mutex_unlock(&philo->eaten_times_mutex);
}
