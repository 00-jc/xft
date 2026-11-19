/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_io_uring_setup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/19 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/linux/uring.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# if defined(__x86_64__) && !defined(XFT_REQUIRE_LIBC)

__attribute__((__nonnull__(2, 3), __always_inline__, __used__))
inline t_result	xft_io_uring_setup(t_u32 entries,
	t_io_uring_params *restrict params, int *restrict const fd)
{
	int	ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"((long)xft_sys_io_uring_setup),
		"D"((long)entries),
		"S"(params)
		: "rcx", "r11", "memory"
	);
	*fd = (int)ret;
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)-ret, 0)});
}

# endif

#endif
