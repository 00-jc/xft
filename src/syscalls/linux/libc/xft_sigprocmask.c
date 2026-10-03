/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_sigprocmask.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:17:37 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 03:20:03 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_syscalls.h"
#include "types/signal_types.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __used__))
inline int	xft_sigprocmask(t_u32a flags, t_sigset *__restrict__ const set,
	t_sigset *__restrict__ const oldest)
{
	return ((int)syscall(SYS_RT_SIGPROCMASK, flags, set, oldest,
			XFT_SIGSET_SIZE));
}

# endif

#endif
