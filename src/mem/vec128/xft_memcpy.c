/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memcpy_128(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	t_vu128a		x[2];

	x[0] = ((t_blk128r)src)[0];
	x[1] = *((t_blk128r)xft_overlap(src, sizeof(t_vu128a), n));
	*((t_blk128w)dest) = x[0];
	*((t_blk128w)xft_overlap(dest, sizeof(t_vu128a), n)) = x[1];
}

__attribute__((__nonnull__(1, 2), __always_inline__, __used__))
inline void	xft_memmove_128(t_any dest, t_cany const src, t_size n)
{
	t_vu128a		x[2];

	x[0] = ((t_blk128r)src)[0];
	x[1] = *((t_blk128r)xft_overlap(src, sizeof(t_vu128a), n));
	*((t_blk128w)dest) = x[0];
	*((t_blk128w)xft_overlap(dest, sizeof(t_vu128a), n)) = x[1];
}
