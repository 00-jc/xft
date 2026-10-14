/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_masked_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/14 12:47:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_vmanip.h"

#if XFT_HAS_512_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__, __always_inline__, __flatten__))
inline t_nvec	xft_vmask_load(t_cany ptr, t_nmask mask)
{
	return (xft_vmask_load512(ptr, mask));
}

#elif XFT_HAS_256_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__, __always_inline__, __flatten__))
inline t_nvec	xft_vmask_load(t_cany ptr, t_nmask mask)
{
	return (xft_vmask_load256(ptr, mask));
}

#elif XFT_HAS_128_VEC

__attribute__((__nonnull__(1), pure, __no_sanitize_address__, __always_inline__, __flatten__))
inline t_nvec	xft_vmask_load(t_cany ptr, t_nmask mask)
{
	return (xft_vmask_load128(ptr, mask));
}

#else

__attribute__((__nonnull__(1), pure, __no_sanitize_address__, __always_inline__, __flatten__))
inline t_nvec	xft_vmask_load(t_cany ptr, t_nmask mask)
{
	t_u8 __attribute__	((uninitialized))	b[8];
	t_u8									lo;

	if (__builtin_expect(mask == 0, 0))
		return ((t_nvec){0});
	lo = (t_u8)xft_memctz_u16(mask);
	b[0] = -((mask >> 0) & 1);
	b[1] = -((mask >> 1) & 1);
	b[2] = -((mask >> 2) & 1);
	b[3] = -((mask >> 3) & 1);
	b[4] = -((mask >> 4) & 1);
	b[5] = -((mask >> 5) & 1);
	b[6] = -((mask >> 6) & 1);
	b[7] = -((mask >> 7) & 1);
	return ((t_nvec){((t_blk8r)ptr)[(0 & b[0]) | (lo & ~b[0])] & b[0],
		((t_blk8r)ptr)[(1 & b[1]) | (lo & ~b[1])] & b[1],
		((t_blk8r)ptr)[(2 & b[2]) | (lo & ~b[2])] & b[2],
		((t_blk8r)ptr)[(3 & b[3]) | (lo & ~b[3])] & b[3],
		((t_blk8r)ptr)[(4 & b[4]) | (lo & ~b[4])] & b[4],
		((t_blk8r)ptr)[(5 & b[5]) | (lo & ~b[5])] & b[5],
		((t_blk8r)ptr)[(6 & b[6]) | (lo & ~b[6])] & b[6],
		((t_blk8r)ptr)[(7 & b[7]) | (lo & ~b[7])] & b[7]});
}

#endif
