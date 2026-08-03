/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef FT_REQUIRE_LIBC

/*
 *	the libc backend is only selected for arches that are neither
 *	x86_64 nor aarch64, i.e. the generic syscall ABI, which has no bare
 *	"open": go through "openat" with AT_FDCWD, like ft_stat goes through
 *	"newfstatat".
 */

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_open(const char *restrict path, int flags)
{
	return ((int)syscall(SYS_OPENAT, AT_FDCWD, path, flags, 0));
}

#endif
