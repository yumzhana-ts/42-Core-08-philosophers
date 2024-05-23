/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:54:41 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:54:46 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (5 == ac || 6 == ac)
	{
		if (parse_input(&table, av))
			return (EXIT_FAILURE);
		if (data_init(&table))
			return (EXIT_FAILURE);
		if (dinner_start(&table))
			return (EXIT_FAILURE);
		if (clean(&table))
			return (EXIT_FAILURE);
	}
	else
		return (c_error(CHECK_ARG_NUMBER));
	return (0);
}
