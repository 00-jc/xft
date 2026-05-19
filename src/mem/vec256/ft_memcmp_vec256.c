/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp_avx256.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 01:50:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if FT_HAS_256_VEC

__attribute__((__nonnull__(1, 2), __always_inline__))
inline ssize_t	ft_memcmp_finalround(const void *restrict const ptr1,
	const void	*restrict const ptr2, size_t offst, size_t n)
{
	t_u32a		mask;
	t_vu256a	load0;
	t_vu256a	load1;
	size_t		diffbyte;

	if (n == 0)
		return (0);
	offst <<= 5;
	load0 = *(t_blk256r)ft_overlap((t_blk8r)ptr1 + offst, sizeof(t_vu256a), n);
	load1 = *(t_blk256r)ft_overlap((t_blk8r)ptr2 + offst, sizeof(t_vu256a), n);
	mask = ft_bitpack256(load0 != load1) & ft_roll_mask(sizeof(t_vu256a), n);
	if (mask)
	{
		diffbyte = ft_memctz_u32(mask);
		return (load0[diffbyte] - load1[diffbyte]);
	}
	return (0);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline ssize_t	ft_memcmp_avx256(const void *restrict const ptr1,
	const void	*restrict const ptr2, size_t n)
{
	t_u32a		mask;
	t_vu256a	load0;
	t_vu256a	load1;
	size_t		offst;
	size_t		diffb;

	offst = 0;
	if (n < sizeof(t_vu256))
		return (ft_memcmp_minimal(ptr1, ptr2, offst, n));
	while (n >= sizeof(t_vu256))
	{
		ft_prefetch0(ptr1, sizeof(t_vu256a) << 1);
		ft_prefetch0(ptr2, sizeof(t_vu256a) << 1);
		load0 = ((t_blk256r)ptr1)[offst];
		load1 = ((t_blk256r)ptr2)[offst];
		mask = ft_bitpack256(load1 != load0);
		diffb = ft_memctz_u32(mask);
		if (mask)
			return (load0[diffb] - load1[diffb]);
		n -= sizeof(t_vu256a);
		++offst;
	}
	return (ft_memcmp_finalround(ptr1, ptr2, offst, n));
}

#endif
