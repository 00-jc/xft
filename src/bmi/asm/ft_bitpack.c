/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitpack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 03:17:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/21 03:16:09 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_bmi.h"

#ifndef __x86_64__

__attribute__((const, __always_inline__))
inline t_u16a	ft_bitpack128(t_vu128a vec)
{
	return ((t_u16a)(
		(vec[0] & 1) | ((vec[1] & 1) << 1)
		| ((vec[2] & 1) << 2) | ((vec[3] & 1) << 3)
		| ((vec[4] & 1) << 4) | ((vec[5] & 1) << 5)
		| ((vec[6] & 1) << 6) | ((vec[7] & 1) << 7)
		| ((vec[8] & 1) << 8) | ((vec[9] & 1) << 9)
		| ((vec[10] & 1) << 10) | ((vec[11] & 1) << 11)
		| ((vec[12] & 1) << 12) | ((vec[13] & 1) << 13)
		| ((vec[14] & 1) << 14) | ((vec[15] & 1) << 15)
	));
}

# if FT_HAS_256_VEC

__attribute__((const, __always_inline__))
inline t_u32a	ft_bitpack256(t_vu256a vec)
{
	t_vu128a	hi;
	t_vu128a	lo;

	lo = ((t_blk128ra) & vec)[0];
	hi = ((t_blk128ra) & vec)[1];
	return ((ft_bitpack128(lo)
			| (((t_u32a)ft_bitpack128(hi)) << 16)));
}

# endif

# if FT_HAS_512_VEC

__attribute__((const, __always_inline__))
inline t_u64a	ft_bitpack512(t_vu512a vec)
{
	t_vu256a	hi;
	t_vu256a	lo;

	lo = ((t_blk256ra) & vec)[0];
	hi = ((t_blk256ra) & vec)[1];
	return ((ft_bitpack256(lo)
			| (((t_u64a)ft_bitpack256(hi)) << 32)));
}

# endif

#endif
