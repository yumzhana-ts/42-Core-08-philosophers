/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_bool.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:55:17 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:55:22 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return true/false Lines:✅ 
bool	is_error(t_bool result)
{
	if (result.error == 1)
		return (true);
	return (false);
}

//🛡️: return true/false Lines:✅
bool	is_true(t_bool result)
{
	if (result.error == 0 && result.value == true)
		return (true);
	return (false);
}
