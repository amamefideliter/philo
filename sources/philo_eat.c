/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:14:43 by dzubkova          #+#    #+#             */
/*   Updated: 2024/09/24 13:33:36 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static void	update_meal_fields(t_philo *philo);
static int	left_first(t_philo *philo, int right, int left);
static int	right_first(t_philo *philo, int right, int left);

int	eat(t_philo *philo)
{
	int	left;
	int	right;

	if (is_somebody_dead(philo))
		return (EXIT);
	left = philo->idx;
	right = (left + 1) % philo->state->nb_philos;
	if (philo->idx % 2)
	{
		if (right_first(philo, right, left))
			return (EXIT);
	}
	else
	{
		if (left_first(philo, right, left))
			return (EXIT);
	}
	print_message(EAT, philo);
	update_meal_fields(philo);
	usleep(philo->state->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->state->forks[left]);
	pthread_mutex_unlock(&philo->state->forks[right]);
	return (SUCCESS);
}

static int	right_first(t_philo *philo, int right, int left)
{
	pthread_mutex_lock(&philo->state->forks[right]);
	if (is_somebody_dead(philo))
	{
		pthread_mutex_unlock(&philo->state->forks[right]);
		return (EXIT);
	}
	print_message(FORK, philo);
	pthread_mutex_lock(&philo->state->forks[left]);
	if (is_somebody_dead(philo))
	{
		pthread_mutex_unlock(&philo->state->forks[left]);
		pthread_mutex_unlock(&philo->state->forks[right]);
		return (EXIT);
	}
	print_message(FORK, philo);
	return (SUCCESS);
}

static int	left_first(t_philo *philo, int right, int left)
{
	pthread_mutex_lock(&philo->state->forks[left]);
	if (is_somebody_dead(philo))
	{
		pthread_mutex_unlock(&philo->state->forks[left]);
		return (EXIT);
	}
	print_message(FORK, philo);
	pthread_mutex_lock(&philo->state->forks[right]);
	if (is_somebody_dead(philo))
	{
		pthread_mutex_unlock(&philo->state->forks[left]);
		pthread_mutex_unlock(&philo->state->forks[right]);
		return (EXIT);
	}
	print_message(FORK, philo);
	return (SUCCESS);
}

static void	update_meal_fields(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->last_meal_mtx);
	pthread_mutex_lock(&philo->eaten_times_mutex);
	philo->eaten_times++;
	pthread_mutex_unlock(&philo->eaten_times_mutex);
}
