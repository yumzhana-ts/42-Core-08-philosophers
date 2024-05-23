/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:54:27 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:54:30 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

//🛡️: return struct {VALUE/0} or {False/1} Lines: 🦉
static t_bool	is_error_dead(t_philo *philo)
{
	t_bool	exit;

	if (is_error(get_bool(&philo->philo_mutex, &philo->full)))
	{
		exit.error = 1;
		exit.value = false;
		return (exit);
	}
	if (!get_time(MILLISECOND))
	{
		exit.error = 1;
		exit.value = false;
		return (exit);
	}
	if (!get_long(&philo->philo_mutex,
			&philo->last_meal_time))
	{
		exit.error = 1;
		exit.value = false;
		return (exit);
	}
	return (exit);
}

//🛡️: return struct {VALUE/0} or {False/1} Lines: 🦉
static t_bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;
	t_bool	exit;

	exit = is_error_dead(philo);
	if (is_true(get_bool(&philo->philo_mutex, &philo->full)))
	{
		exit.error = 0;
		exit.value = false;
		return (exit);
	}
	elapsed = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > t_to_die)
	{
		exit.error = 0;
		exit.value = true;
		return (exit);
	}
	exit.error = 0;
	exit.value = false;
	return (exit);
}

void	*wait_sync(void *data)
{
	t_table		*table;

	table = (t_table *)data;
	if (is_error(all_threads_running(&table->table_mutex,
				&table->threads_running_nbr, table->philo_nbr)))
		return (NULL);
	while (!is_true(all_threads_running(&table->table_mutex,
				&table->threads_running_nbr, table->philo_nbr)));
	return (NULL);
}

//🛡️: return NULL Lines: 🦉
void	*monitor_dinner(void *data)
{
	int			i;
	t_table		*table;

	table = (t_table *)data;
	wait_sync(data);
	if (is_error(simulation_finished(table)))
		return (NULL);
	while (!is_true(simulation_finished(table)))
	{
		i = -1;
		while (++i < table->philo_nbr && !is_true(simulation_finished(table)))
		{
			if (is_error(philo_died(table->philos + i)))
				return (NULL);
			if (is_true(philo_died(table->philos + i)))
			{
				if (set_bool(&table->table_mutex, &table->end_simulation, true))
					return (NULL);
				if (write_status(DIED, table->philos + i, DEBUG_MODE))
					return (NULL);
			}
		}
	}
	return (NULL);
}
