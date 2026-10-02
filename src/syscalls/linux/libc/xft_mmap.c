/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/02 20:14:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __used__))
inline t_any	xft_mmap(t_size size, t_u64a prot, t_u64a flags_extra)
{
	return ((t_any)syscall(SYS_MMAP,
			(t_any)0,
			size,
			prot,
			MAP_ANONYMOUS | MAP_PRIVATE | flags_extra,
			-1,
			0
		));
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_munmap(t_any restrict const mem, t_size size)
{
	syscall(SYS_MUNMAP, mem, size);
}

# endif

#endif
