/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/09 14:37:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#if defined(__aarch64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__always_inline__))
inline t_any	ft_fmap(t_size size, int fd)
{
	long	args[6];

	args[0] = (long) NULL;
	args[1] = (long)size;
	args[2] = PROT_READ;
	args[3] = MAP_PRIVATE;
	args[4] = fd;
	args[5] = 0;
	return ((t_any)ft_syscall6(SYS_MMAP, args));
}

#endif
