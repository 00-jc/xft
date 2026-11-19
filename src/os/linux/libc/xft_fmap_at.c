/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_fmap_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __used__, __nonnull__(4)))
inline t_any	xft_fmap_at(t_size size, t_u64a prot, t_u64a flags,
	const t_u64a at[2])
{
	return ((t_any)syscall(xft_libc_sys_mmap, (t_any)0, size, (long)prot,
			(long)flags, (long)at[0], (long)at[1]));
}

# endif

#endif
