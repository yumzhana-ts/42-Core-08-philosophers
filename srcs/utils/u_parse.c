/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:10 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:57:13 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return 0 or 1 Lines: ✅
int	parse_philosopher_number(t_table *table, char *arg)
{
	table->philo_nbr = ft_atol(arg);
	if (!table->philo_nbr)
		return (1);
	if (table->philo_nbr > PHILO_MAX)
		return (c_error(INVALID_MAX_PHILO));
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	parse_time_to_die(t_table *table, char *arg)
{
	table->time_to_die = ft_atol(arg) * 1e3;
	if (!table->time_to_die)
		return (1);
	if (table->time_to_die < 6e4)
		return (c_error(INVALID_TIMESTAMP));
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	parse_time_to_eat(t_table *table, char *arg)
{
	table->time_to_eat = ft_atol(arg) * 1e3;
	if (!table->time_to_eat)
		return (1);
	if (table->time_to_eat < 6e4)
		return (c_error(INVALID_TIMESTAMP));
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	parse_time_to_sleep(t_table *table, char *arg)
{
	table->time_to_sleep = ft_atol(arg) * 1e3;
	if (!table->time_to_sleep)
		return (1);
	if (table->time_to_sleep < 6e4)
		return (c_error(INVALID_TIMESTAMP));
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	parse_nbr_limit_meals(t_table *table, char *arg)
{
	if (arg)
	{
		table->nbr_limit_meals = ft_atol(arg);
		if (!table->nbr_limit_meals)
			return (1);
	}
	else
		table->nbr_limit_meals = -1;
	return (0);
}
