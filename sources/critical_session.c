/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   critical_session.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:24:02 by daria             #+#    #+#             */
/*   Updated: 2024/09/24 13:33:27 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if (philo->state->nb_philos == 1)
	{
		usleep(philo->state->time_to_die);
		return (NULL);
	}
	while (1)
	{
		if (eat(philo))
			return (NULL);
		if (philo_sleep(philo))
			return (NULL);
		if (think(philo))
			return (NULL);
	}
}

int	philo_sleep(t_philo *philo)
{
	if (is_somebody_dead(philo))
		return (EXIT);
	print_message(SLEEP, philo);
	usleep(philo->state->time_to_sleep * 1000);
	return (SUCCESS);
}

int	think(t_philo *philo)
{
	if (is_somebody_dead(philo))
		return (EXIT);
	print_message(THINK, philo);
	usleep(philo->state->time_to_eat + philo->state->time_to_sleep);
	return (SUCCESS);
}
