/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_set_thread_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 15:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 15:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline int	xft_set_thread_pointer(t_uptr tp)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_arch_prctl), "D"((long)xft_arch_set_fs),
		"S"(tp)
		: "rcx", "r11", "memory"
	);
	return ((int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
