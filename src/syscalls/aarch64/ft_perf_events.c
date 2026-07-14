/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perf_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef __aarch64__

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_perf_event_open(const t_perf_event_attr *restrict attr,
		int group_fd)
{
	long	args[6];

	args[0] = (long)attr;
	args[1] = 0;
	args[2] = -1;
	args[3] = group_fd;
	args[4] = PERF_FLAG_FD_CLOEXEC;
	args[5] = 0;
	return ((int)ft_syscall6(SYS_PERF_EVENT_OPEN, args));
}

#endif
