/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memcpy_64(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	t_u64a		x[2];

	x[0] = ((t_blk64r)src)[0];
	x[1] = *((t_blk64r)xft_overlap(src, sizeof(t_u64a), n));
	((t_blk64w)dest)[0] = x[0];
	*((t_blk64w)xft_overlap(dest, sizeof(t_u64a), n)) = x[1];
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memmove_64(t_any dest, t_cany const src, t_size n)
{
	t_u64a		x[2];

	x[0] = ((t_blk64r)src)[0];
	x[1] = *((t_blk64r)xft_overlap(src, sizeof(t_u64a), n));
	((t_blk64w)dest)[0] = x[0];
	*((t_blk64w)xft_overlap(dest, sizeof(t_u64a), n)) = x[1];
}
