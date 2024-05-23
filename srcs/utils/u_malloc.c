/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:56:23 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:56:27 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return mem or NULL Lines: ✅
void	*malloc_handler(size_t bytes)
{
	void	*memory_block;

	memory_block = malloc(bytes);
	if (memory_block == NULL)
	{
		c_error(INVALID_MALLOC);
		return (NULL);
	}
	return (memory_block);
}
