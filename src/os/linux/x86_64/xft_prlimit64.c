/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_prlimit64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 23:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/28 23:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(4), __always_inline__, __used__))
inline int	xft_prlimit64(t_i32a pid, t_xft_rlimit resource,
	const t_rlimit *new_limit, t_rlimit *__restrict__ old_limit)
{
	int					ret;
	register long r10	__asm__("r10");

	r10 = (long)old_limit;
	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_prlimit64),
		"D"((long)pid),
		"S"((long)resource),
		"d"(new_limit),
		"r"(r10)
		: "rcx", "r11", "memory"
	);
	return ((int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
