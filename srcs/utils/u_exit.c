/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:55:52 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:55:55 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return 0 or 1 Lines: ✅
int	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos + i;
		if (mutex_handler(&philo->philo_mutex, DESTROY))
			return (1);
	}
	if (mutex_handler(&table->write_mutex, DESTROY))
		return (1);
	if (mutex_handler(&table->table_mutex, DESTROY))
		return (1);
	free(table->forks);
	free(table->philos);
	return (0);
}

//🛡️: return 1 Lines: ✅
int	ft_putstr_fd(char *s)
{
	int	i;
	int	p;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			p = write(2, &s[i], 1);
			i++;
		}
	}
	p = 1;
	return (p);
}

//🛡️: return 0 or 1 Lines: ✅
int	c_error(t_errors errors)
{
	if (errors == CHECK_ARG_NUMBER)
		return (ft_putstr_fd(RED"Incorrect format:"
				"try ./philo 5 800 200 200 [7]\n"RST));
	else if (errors == INVALID_MAX_PHILO)
		return (ft_putstr_fd(RED"Number of philos is above the limit\n"RST));
	else if (errors == INVALID_TIMESTAMP)
		return (ft_putstr_fd(RED"Use timestamps major than 60ms\n"RST));
	else if (errors == INVALID_INT)
		return (ft_putstr_fd(RED"INT_MAX is the limit, not the sky\n"RST));
	else if (errors == NEGATIVE_VALUE)
		return (ft_putstr_fd(RED"Feed me only positive values\n"RST));
	else if (errors == NOT_DIGIT)
		return (ft_putstr_fd(RED"The input is not a correct digit\n"RST));
	else if (errors == INVALID_MALLOC)
		return (ft_putstr_fd(RED"Error with the malloc\n"RST));
	else if (errors == WRONG_MUTEX_OP)
		return (ft_putstr_fd(RED"Wrong opcode for mutex_handle\n"RST));
	else if (errors == WRONG_THREAD_OP)
		return (ft_putstr_fd(RED"Wrong opcode for thread_handle\n"RST));
	else if (errors == FAILED_GET_TIME)
		return (ft_putstr_fd(RED"Get time of day failed\n"RST));
	else if (errors == WRONG_TIME_OP)
		return (ft_putstr_fd(RED"Wrong opcode for timehandle\n"RST));
	return (0);
}
