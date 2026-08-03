/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_failed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 02:41:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/03 02:41:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syscalls.h"

/*
 *	Band test for the mmap family, which is the one group of syscalls
 *	that does not fold its errors down to -1 (see syscalls.h). Testing
 *	a return against MAP_FAILED alone only catches -EPERM; every other
 *	errno reads as a plausible address and gets written through. The
 *	libc backend is covered as well, its -1 sits inside the same band.
 */

__attribute__((const, __hot__, __always_inline__))
inline t_result	ft_map_failed(t_cany ptr)
{
	return ((t_uptr)ptr >= (t_uptr)-FT_MAX_ERRNO);
}
