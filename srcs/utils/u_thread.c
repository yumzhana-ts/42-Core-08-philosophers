/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_thread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytsyrend <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:37 by ytsyrend          #+#    #+#             */
/*   Updated: 2024/03/06 15:57:40 by ytsyrend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/philosophers.h"

//🛡️: return 0 or 1 Lines: ✅
static int	handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return (0);
	if (EAGAIN == status)
		return (ft_putstr_fd("No resources to create another thread"));
	else if (EPERM == status)
		return (ft_putstr_fd("The caller does"
				"not have appropriate permission\n"));
	else if (EINVAL == status && CREATE == opcode)
		return (ft_putstr_fd("The value specified by attr is invalid."));
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		return (ft_putstr_fd("The value specified"
				"by thread is not joinable\n"));
	else if (ESRCH == status)
		return (ft_putstr_fd("No thread could be found corresponding to that"
				"specified by the given thread ID, thread."));
	else if (EDEADLK == status)
		return (ft_putstr_fd("A deadlock was detected or the value of"
				"thread specifies the calling thread."));
	return (0);
}

//🛡️: return 0 or 1 Lines: ✅
int	thread_handler(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		return (handle_thread_error(pthread_create
				(thread, NULL, foo, data), opcode));
	else if (opcode == JOIN)
		return (handle_thread_error(pthread_join(*thread, NULL), opcode));
	else if (opcode == DETACH)
		return (handle_thread_error(pthread_detach(*thread), opcode));
	else
		return (c_error(WRONG_THREAD_OP));
	return (0);
}
