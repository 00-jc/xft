/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prefetch_intrin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

#ifdef __x86_64__

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_prefetch0(const void *restrict const ptr,
	t_size distance)
{
	t_u8	*addr;

	addr = (t_u8 *)ptr + distance;
	__asm__(
		"prefetcht0 %0"
		:
		: "m"(*addr)
		);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_prefetch1(const void *restrict const ptr,
	t_size distance)
{
	t_u8	*addr;

	addr = (t_u8 *)ptr + distance;
	__asm__(
		"prefetcht1 %0"
		:
		: "m"(*addr)
		);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_prefetch2(const void *restrict const ptr,
	t_size distance)
{
	t_u8	*addr;

	addr = (t_u8 *)ptr + distance;
	__asm__(
		"prefetcht2 %0"
		:
		: "m"(*addr)
		);
}

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_prefetchnta(const void *restrict const ptr,
	t_size distance)
{
	t_u8	*addr;

	addr = (t_u8 *)ptr + distance;
	__asm__(
		"prefetchnta %0"
		:
		: "m"(*addr)
		);
}

#endif
