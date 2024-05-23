/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:56:14 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:56:17 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_non_digit(const char *str)
{
	if (!is_digit(*str))
	{
		c_error(NOT_DIGIT);
		return (0);
	}
	return (1);
}
