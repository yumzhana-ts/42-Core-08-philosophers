/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_mutex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:56:36 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:56:59 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return 0 or 1 Lines: ✅
static int	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return (0);
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		return (ft_putstr_fd("The value specified by mutex is invalid"));
	else if (EINVAL == status && INIT == opcode)
		return (ft_putstr_fd("The value specified by attr is invalid."));
	else if (EDEADLK == status)
		return (ft_putstr_fd("A deadlock would occur if the thread "
				"blocked waiting for mutex."));
	else if (EPERM == status)
		return (ft_putstr_fd("The current thread "
				"does not hold a lock on mutex."));
	else if (ENOMEM == status)
		return (ft_putstr_fd("The process cannot allocate enough memory"
				" to create another mutex."));
	else if (EBUSY == status)
		return (ft_putstr_fd("Mutex is locked"));
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	mutex_handler(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == INIT)
		return (handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode));
	else if (opcode == LOCK)
		return (handle_mutex_error(pthread_mutex_lock(mutex), opcode));
	else if (opcode == UNLOCK)
		return (handle_mutex_error(pthread_mutex_unlock(mutex), opcode));
	else if (opcode == DESTROY)
		return (handle_mutex_error(pthread_mutex_destroy(mutex), opcode));
	else
		return (c_error(WRONG_MUTEX_OP));
	return (0);
}
