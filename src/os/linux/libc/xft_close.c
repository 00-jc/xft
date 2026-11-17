/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_syscalls.h>

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__always_inline__, __used__))
inline t_xft_sysres	xft_close(int fd)
{
	return ((t_xft_sysres)(syscall(SYS_close, fd) == 0 || errno == EINTR));
}

# endif

#endif
