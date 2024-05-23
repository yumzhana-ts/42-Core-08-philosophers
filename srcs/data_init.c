/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:53:45 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:53:51 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks,
		int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;
	philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
	}
}

//🛡️: return 0 or 1 Lines: ✅
int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		if (mutex_handler(&philo->philo_mutex, INIT))
			return (1);
		philo->table = table;
		assign_forks(philo, table->forks, i);
	}
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	data_init(t_table *table)
{
	int		i;

	i = -1;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->threads_running_nbr = 0;
	table->philos = malloc_handler(table->philo_nbr * sizeof(t_philo));
	if (table->philos == NULL)
		return (1);
	table->forks = malloc_handler(table->philo_nbr * sizeof(t_fork));
	if (table->forks == NULL)
		return (1);
	if (mutex_handler(&table->write_mutex, INIT))
		return (1);
	if (mutex_handler(&table->table_mutex, INIT))
		return (1);
	while (++i < table->philo_nbr)
	{
		if (mutex_handler(&table->forks[i].fork, INIT))
			return (1);
		table->forks[i].fork_id = i;
	}
	if (philo_init(table))
		return (1);
	return (0);
}
