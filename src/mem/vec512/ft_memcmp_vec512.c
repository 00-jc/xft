/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp_vec512.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:42 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/08 03:06:18 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

#if FT_HAS_512_VEC

__attribute__((__nonnull__(1, 2), __always_inline__))
inline t_ssize	ft_memcmp_finalround(const void *restrict const ptr1,
	const void	*restrict const ptr2, t_size offst, t_size n)
{
	t_u64a		mask;
	t_vu512a	load0;
	t_vu512a	load1;
	t_size		diffbyte;

	if (n == 0)
		return (0);
	offst <<= 6;
	load0 = *(t_blk512r)ft_overlap((t_blk8r)ptr1 + offst, sizeof(t_vu512a), n);
	load1 = *(t_blk512r)ft_overlap((t_blk8r)ptr2 + offst, sizeof(t_vu512a), n);
	mask = ft_bitpack512((t_vu512a)(load0 != load1))
		& ft_roll_mask(sizeof(t_vu512a), n);
	if (mask)
	{
		diffbyte = ft_memctz_u64(mask);
		return (load0[diffbyte] - load1[diffbyte]);
	}
	return (0);
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline t_ssize	ft_memcmp_avx512(const void *restrict const ptr1,
	const void	*restrict const ptr2, t_size n)
{
	t_u64a		mask;
	t_vu512a	load0;
	t_vu512a	load1;
	t_size		offst;
	t_size		diffb;

	offst = 0;
	if (n < sizeof(t_vu512))
		return (ft_memcmp_minimal(ptr1, ptr2, offst, n));
	while (n >= sizeof(t_vu512))
	{
		ft_prefetch0(ptr1, sizeof(t_vu512a) << 1);
		ft_prefetch0(ptr2, sizeof(t_vu512a) << 1);
		load0 = ((t_blk512r)ptr1)[offst];
		load1 = ((t_blk512r)ptr2)[offst];
		mask = ft_bitpack512((t_vu512a)(load1 != load0));
		diffb = ft_memctz_u64(mask);
		if (mask)
			return (load0[diffb] - load1[diffb]);
		n -= sizeof(t_vu512a);
		++offst;
	}
	return (ft_memcmp_finalround(ptr1, ptr2, offst, n));
}

#endif
