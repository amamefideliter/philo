/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:40:21 by dzubkova          #+#    #+#             */
/*   Updated: 2024/09/24 13:41:14 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philos.h"

static int	unpack_arguments(char **argv, int argc, t_state *state);
static int	check_arguments(t_state *state);

int	main(int argc, char **argv)
{
	t_state	state;

	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Usage: number_of_philosophers ", STDERR_FILENO);
		ft_putstr_fd("time_to_eat time_to_sleep ", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
		return (ERROR);
	}
	else if (unpack_arguments(argv, argc, &state))
	{
		ft_putstr_fd("ERROR: Arguments must be positive integers\n", 2);
		return (ERROR);
	}
	if (run_simulation(&state))
		return (ERROR);
	return (SUCCESS);
}

static int	unpack_arguments(char **argv, int argc, t_state *state)
{
	state->nb_philos = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		state->meal_count = ft_atoi(argv[5]);
		if (state->meal_count < 1)
			return (ERROR);
	}
	else
		state->meal_count = NOT_SET;
	state->exit = NOT_SET;
	state->s_start = NOT_SET;
	if (check_arguments(state))
		return (ERROR);
	return (SUCCESS);
}

static int	check_arguments(t_state *state)
{
	if (state->nb_philos < 1)
		return (ERROR);
	if (state->time_to_die < 0)
		return (ERROR);
	if (state->time_to_eat < 0)
		return (ERROR);
	if (state->time_to_sleep < 0)
		return (ERROR);
	return (SUCCESS);
}
