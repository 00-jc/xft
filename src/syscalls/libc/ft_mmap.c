/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/04 13:15:08 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef FT_REQUIRE_LIBC

__attribute__((__always_inline__))
t_any	ft_mmap(t_size size, long prot, long flags_extra)
{
	return ((t_any)syscall(SYS_MMAP,
			size,
			NULL,
			prot,
			0,
			-1,
			MAP_ANONYMOUS | MAP_PRIVATE | flags_extra
		));
}

__attribute__((nonnull(1), __always_inline__))
inline void	ft_munmap(t_any restrict const mem, t_size size)
{
	syscall(SYS_MUNMAP, mem, size);
}

#endif
