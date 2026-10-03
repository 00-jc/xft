/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_mprotect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 09:54:35 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 02:53:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_syscalls.h"
#include "syscalls.h"

#ifdef __linux__

# ifdef XFT_REQUIRE_LIBC

__attribute__((__nonnull__(1)))
int	xft_mprotect(t_any addr, t_size size, int prot)
{
	return ((int)syscall(SYS_MPROTECT, addr, size, prot));
}

# endif

#endif
