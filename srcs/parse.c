/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:54:15 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:54:19 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/philosophers.h"

//return 0 or CHAR Lines: ✅
static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
	{
		c_error(NEGATIVE_VALUE);
		return (0);
	}
	is_non_digit(str);
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
	{
		c_error(INVALID_INT);
		return (0);
	}
	return (number);
}

//return 0 or LONG Lines: ✅
long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (!str)
		return (0);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
	{
		c_error(INVALID_INT);
		return (0);
	}
	return (num);
}

//return 1 or 0 Lines: ✅
int	parse_input(t_table *table, char **av)
{
	if (parse_philosopher_number(table, av[1])
		|| parse_time_to_die(table, av[2])
		|| parse_time_to_eat(table, av[3])
		|| parse_time_to_sleep(table, av[4])
		|| parse_nbr_limit_meals(table, av[5]))
		return (1);
	return (0);
}
