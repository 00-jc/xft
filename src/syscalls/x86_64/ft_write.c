/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "bmi.h"
#include "private/ft_p_syscalls.h"

#if defined(__x86_64__) && !defined(FT_REQUIRE_LIBC)

__attribute__((__nonnull__(2), __always_inline__))
inline t_ssize	ft_write(int fd, t_u8 *restrict const buffer, t_size len)
{
	t_ssize		ret;

	__asm__ volatile (
		"syscall"
		: "=a"(ret)
		: "0"(SYS_WRITE),
		"D"(fd),
		"S"(buffer),
		"d"(len)
		: "rcx", "r11", "memory"
	);
	return ((t_ssize)ft_tern(ret < 0, (t_u64a)-1, (t_u64a)ret));
}

#endif
