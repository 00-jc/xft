/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sched_getaffinity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:21:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/15 11:28:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef FT_REQUIRE_LIBC

__attribute__((__nonnull__(3), __always_inline__))
inline int	ft_sched_getaffinity(t_i32a pid, t_size cpusetsize,
		const t_u64a *__restrict__ mask)
{
	return ((int)syscall(SYS_SCHED_GETAFFINITY, pid, cpusetsize, mask));
}

#endif
