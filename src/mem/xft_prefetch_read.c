/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_prefetch_read.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_prefetch_read0(t_cany restrict const ptr,
	t_size distance)
{
	__builtin_prefetch((const t_u8 *)ptr + distance, 0, 3);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_prefetch_read1(t_cany restrict const ptr,
	t_size distance)
{
	__builtin_prefetch((const t_u8 *)ptr + distance, 0, 2);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_prefetch_read2(t_cany restrict const ptr,
	t_size distance)
{
	__builtin_prefetch((const t_u8 *)ptr + distance, 0, 1);
}

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_prefetch_readnta(t_cany restrict const ptr,
	t_size distance)
{
	__builtin_prefetch((const t_u8 *)ptr + distance, 0, 0);
}
