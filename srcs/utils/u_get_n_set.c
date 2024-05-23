/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_get_n_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:56:02 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:56:05 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return 0 or 1 Lines: ✅
int	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	if (mutex_handler(mutex, LOCK))
		return (1);
	*dest = value;
	if (mutex_handler(mutex, UNLOCK))
		return (1);
	return (0);
}

//🛡️: return struct {VALUE/0} or {False/1} Lines: ✅
t_bool	get_bool(t_mtx *mutex, bool *value)
{
	t_bool	result;

	if (mutex_handler(mutex, LOCK))
	{
		result.error = 1;
		result.value = false;
		return (result);
	}
	result.value = *value;
	result.error = 0;
	if (mutex_handler(mutex, UNLOCK))
	{
		result.error = 1;
		result.value = false;
		return (result);
	}
	return (result);
}

//🛡️: return 0 or 1 Lines: ✅
int	set_long(t_mtx *mutex, long *dest, long value)
{
	if (mutex_handler(mutex, LOCK))
		return (1);
	*dest = value;
	if (mutex_handler(mutex, UNLOCK))
		return (1);
	return (0);
}

//🛡️: return value or 0 Lines: ✅
long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	if (mutex_handler(mutex, LOCK))
		return (0);
	ret = *value;
	if (mutex_handler(mutex, UNLOCK))
		return (0);
	return (ret);
}

//🛡️: return struct {VALUE/0} or {False/1} Lines: ✅
t_bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}
