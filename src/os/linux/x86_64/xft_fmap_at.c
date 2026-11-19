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

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__, __nonnull__(4)))
inline t_any	xft_fmap_at(t_size size, t_u64a prot, t_u64a flags,
	const t_u64a at[2])
{
	t_any				ret;
	register long r10	__asm__("r10");
	register long r8	__asm__("r8");
	register long r9	__asm__("r9");

	r10 = flags;
	r8 = (long)at[0];
	r9 = (long)at[1];
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_mmap),
		"D"((long)0),
		"S"((long) size),
		"d"(prot),
		"r"(r10), "r"(r8), "r"(r9)
		: "rcx", "r11", "memory"
	);
	return (ret);
}

# endif

#endif
