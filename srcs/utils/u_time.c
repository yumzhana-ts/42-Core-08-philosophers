/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_time.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:53 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:57:56 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return 0 or INT Lines: ✅
long	get_time(int time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		c_error(WRONG_TIME_OP);
		return (0);
	}
	if (time_code == MILLISECOND)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (time_code == MICROSECOND)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (time_code == SECONDS)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
	{
		c_error(WRONG_TIME_OP);
		return (0);
	}
	return (1337);
}

//🛡️: return 0 or 1 Lines: ✅
int	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	if (!get_time(MICROSECOND))
		return (1);
	start = get_time(MICROSECOND);
	while (get_time(MICROSECOND) - start < usec)
	{
		if (is_error(simulation_finished(table)))
			return (1);
		if (is_true(simulation_finished(table)))
			break ;
		elapsed = get_time(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e4)
			usleep(rem / 2);
		else
			while (get_time(MICROSECOND) - start < usec)
				;
	}
	return (0);
}
