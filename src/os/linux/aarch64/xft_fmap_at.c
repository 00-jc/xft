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

# if defined(__aarch64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__, __nonnull__(4)))
inline t_any	xft_fmap_at(t_size size, t_u64a prot, t_u64a flags,
	const t_u64a at[2])
{
	t_u64a	args[6];

	args[0] = 0;
	args[1] = (t_u64a)size;
	args[2] = prot;
	args[3] = flags;
	args[4] = at[0];
	args[5] = at[1];
	return ((t_any)xft_syscall6(xft_sys_mmap, args));
}

# endif

#endif
