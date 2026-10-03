/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_ioctl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "linux.h"
#include "xft_p_syscalls.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __used__))
inline int	xft_ioctl(int fd, t_u64a request, t_u64a arg)
{
	return ((int)syscall(SYS_IOCTL, fd, request, arg));
}

# endif

#endif
