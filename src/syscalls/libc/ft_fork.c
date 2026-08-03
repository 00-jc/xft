/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/30 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "signals.h"
#include "private/ft_p_syscalls.h"

#ifdef FT_REQUIRE_LIBC

/*
 *	SYS_FORK only exists on some architectures (aarch64 has none), so
 *	the libc backend goes through clone(SIGCHLD, 0, 0, 0, 0) like
 *	ft_stat goes through newfstatat: same semantics everywhere. The
 *	trailing NULLs make the ctid/tls argument order irrelevant.
 */

__attribute__((__always_inline__))
inline t_i32	ft_fork(void)
{
	return ((t_i32)syscall(SYS_CLONE, FT_SIGCHLD, 0, 0, 0, 0));
}

#endif
