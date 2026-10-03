/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sched_setaffinity.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(3), __always_inline__, __used__))
inline int	xft_sched_setaffinity(int pid, t_size cpusetsize,
		const t_u64a *restrict const mask)
{
	return ((int)syscall(SYS_SCHED_SETAFFINITY, pid, cpusetsize, mask));
}

# endif

#endif
