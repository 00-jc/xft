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

#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(4), __always_inline__, __used__))
inline int	xft_prlimit64(t_i32a pid, t_xft_rlimit resource,
		const t_rlimit *new_limit, t_rlimit *__restrict__ old_limit)
{
	return ((int)syscall(SYS_prlimit64, (long)pid, (long)resource,
			new_limit, old_limit));
}

# endif

#endif
