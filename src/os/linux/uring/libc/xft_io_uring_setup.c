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

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(2, 3), __always_inline__, __used__))
inline t_result	xft_io_uring_setup(t_u32 entries,
	t_io_uring_params *restrict params, int *restrict const fd)
{
	t_ssize	ret;

	ret = syscall(SYS_io_uring_setup, entries, params);
	*fd = (int)ret;
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

# endif

#endif
