/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_synchro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:23 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:57:29 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return 1 or 0 Lines: ✅
int	wait_all_threads(t_table *table)
{
	if (is_error(get_bool(&table->table_mutex, &table->all_threads_ready)))
		return (1);
	while (!is_true(get_bool
			(&table->table_mutex, &table->all_threads_ready)));
	return (0);
}

//🛡️: return 1 or 0 Lines: ✅
int	increase_long(t_mtx *mutex, long *value)
{
	if (mutex_handler(mutex, LOCK))
		return (1);
	(*value)++;
	if (mutex_handler(mutex, UNLOCK))
		return (1);
	return (0);
}

//🛡️: return struct {VALUE/0} or {False/1} Lines: ✅
t_bool	all_threads_running(t_mtx *mutex, long *threads,
		long philo_nbr)
{
	t_bool	result;
	bool	ret;

	ret = false;
	if (mutex_handler(mutex, LOCK))
	{
		result.error = 1;
		result.value = false;
		return (result);
	}
	if (*threads == philo_nbr)
		ret = true;
	if (mutex_handler(mutex, UNLOCK))
	{
		result.error = 1;
		result.value = false;
		return (result);
	}
	result.value = ret;
	result.error = 0;
	return (result);
}

//🛡️:return 1 or 0 Lines: ✅
int	de_synchronize_philos(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0)
	{
		if (philo->id % 2 == 0)
		{
			if (precise_usleep(3e4, philo->table))
				return (1);
		}
	}
	else
	{
		if (philo->id % 2)
		{
			if (thinking(philo, true))
				return (1);
		}
	}
	return (0);
}
