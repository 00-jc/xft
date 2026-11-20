/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_rt_sigprocmask.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/20 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/bmi.h>
#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __used__))
inline t_result	xft_rt_sigprocmask(t_xft_sighow how, const t_u64a *set,
	t_u64a *oldset)
{
	t_ssize	ret;

	ret = syscall(SYS_rt_sigprocmask, (long)how, set, oldset,
			(long)XFT_SIGSET_SIZE);
	return ((t_result){.ok = ret >= 0,
		.err = xft_tern(ret < 0, (t_u64a)errno, 0)});
}

# endif

#endif
