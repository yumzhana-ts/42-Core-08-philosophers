/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:54:01 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:54:07 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

//🛡️: return NULL Lines: 🦉
static void	*dinner_simulation(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (wait_all_threads(philo->table))
		return (NULL);
	if (set_long(&philo->philo_mutex, &philo->last_meal_time,
			get_time(MILLISECOND)))
		return (NULL);
	if (increase_long(&philo->table->table_mutex,
			&philo->table->threads_running_nbr))
		return (NULL);
	if (de_synchronize_philos(philo))
		return (NULL);
	if (is_error(simulation_finished(philo->table)))
		return (NULL);
	actions(data);
	return (NULL);
}

static int	thread_monitor(t_table *table)
{
	if (thread_handler(&table->monitor, monitor_dinner, table, CREATE))
		return (1);
	if (!get_time(MILLISECOND))
		return (1);
	table->start_simulation = get_time(MILLISECOND);
	if (set_bool(&table->table_mutex, &table->all_threads_ready, true))
		return (1);
	return (0);
}

//🛡️: return NULL Lines: 🦉
int	thread_create(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return (0);
	else if (table->philo_nbr == 1)
	{
		if (thread_handler(&table->philos[0].thread_id, lone_philo,
				&table->philos[0], CREATE))
			return (1);
	}
	else
	{
		while (++i < table->philo_nbr)
		{
			if (thread_handler(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE))
				return (1);
		}
	}
	thread_monitor(table);
	return (0);
}

int	dinner_start(t_table *table)
{
	int			i;

	thread_create(table);
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (thread_handler(&table->philos[i].thread_id, NULL, NULL, JOIN))
			return (1);
	}
	if (set_bool(&table->table_mutex, &table->end_simulation, true))
		return (1);
	if (thread_handler(&table->monitor, NULL, NULL, JOIN))
		return (1);
	return (0);
}
