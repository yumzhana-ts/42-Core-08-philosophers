/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_write.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:58:05 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:58:22 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"
#include <time.h>

//🛡️: return 0 or 1 Lines: ✅
static int	write_status_debug(t_philo_status status, t_philo *philo,
		long elapsed)
{
	if (is_error(simulation_finished(philo->table)))
		return (1);
	if (TAKE_FIRST_FORK == status
		&& !is_true(simulation_finished(philo->table)))
		printf(W"%6ld"RST" %d has taken the 1° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->first_fork->fork_id);
	else if (TAKE_SECOND_FORK == status
		&& !is_true(simulation_finished(philo->table)))
		printf(W"%6ld"RST" %d has taken the 2° fork 🍽"
			"\t\t\tn°"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->second_fork->fork_id);
	else if (EATING == status && !is_true(simulation_finished(philo->table)))
		printf(W"%6ld"C" %d is eating 🍝"
			"\t\t\t"Y"[🍝 %ld 🍝]\n"RST,
			elapsed, philo->id, philo->meals_counter);
	else if (SLEEPING == status && !is_true(simulation_finished(philo->table)))
		printf(W"%6ld"RST" %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && !is_true(simulation_finished(philo->table)))
		printf(W"%6ld"RST" %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t💀💀💀 %6ld %d died   💀💀💀\n"RST, elapsed, philo->id);
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	write_status_norm(t_philo_status status, t_philo *philo, long elap)
{
	long	elapsed;

	elapsed = elap;
	if (is_error(simulation_finished(philo->table)))
		return (1);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !is_true(simulation_finished(philo->table)))
		printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
	else if (EATING == status
		&& !is_true(simulation_finished(philo->table)))
		printf(W"%-6ld"C" %d is eating\n"RST, elapsed, philo->id);
	else if (SLEEPING == status
		&& !is_true(simulation_finished(philo->table)))
		printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
	else if (THINKING == status
		&& !is_true(simulation_finished(philo->table)))
		printf(W"%-6ld"RST" %d is thinking\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	if (!get_time(MILLISECOND))
		return (1);
	elapsed = get_time(MILLISECOND) - philo->table->start_simulation;
	if (is_true(get_bool(&philo->philo_mutex, &philo->full)))
		return (0);
	if (mutex_handler(&philo->table->write_mutex, LOCK))
		return (1);
	if (debug)
	{
		if (write_status_debug(status, philo, elapsed))
			return (1);
	}
	else
	{
		if (write_status_norm(status, philo, elapsed))
			return (1);
	}
	if (mutex_handler(&philo->table->write_mutex, UNLOCK))
		return (1);
	return (0);
}
