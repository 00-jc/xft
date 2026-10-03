/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_set_tid_address.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:51:48 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/08 17:58:30 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmi.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__always_inline__, __used__))
inline int	xft_set_tid_address(t_any address)
{
	int		ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_SET_TID_ADDRESS),
		"D"(address)
		: "rcx", "r11", "memory"
	);
	return ((int)xft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

# endif

#endif
