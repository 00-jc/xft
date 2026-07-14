/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 09:05:43 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 10:28:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"
#include "private/ft_p_syscalls.h"

#ifdef FT_REQUIRE_LIBC

__attribute__((__nonnull__(2), __always_inline__))
inline t_ssize	ft_writev(int fd, t_iovec *restrict const buffers, t_size len)
{
	return (syscall(SYS_WRITEV, fd, buffers, len));
}

#endif
