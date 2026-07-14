/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mremap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"
#include "syscalls.h"

#ifdef FT_REQUIRE_LIBC

__attribute__((__nonnull__(3), __always_inline__))
inline t_any	ft_mremap(t_size size, t_size new_size,
	t_any addr, long flags_extra)
{
	return ((t_any)syscall(SYS_MREMAP, addr, size,
			new_size, MREMAP_MAYMOVE | flags_extra));
}

#endif
