/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_stat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/02 13:45:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline int	xft_stat(const char *restrict path, t_stat *statbuf)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_STAT),
		"D"(path),
		"S"(statbuf)
		: "rcx", "r11", "memory"
	);
	return ((int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
