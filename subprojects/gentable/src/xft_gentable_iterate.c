/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gentable_iterate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 01:59:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/17 03:43:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gentable.h"

__attribute__((__always_inline__, __flatten__, __hot__))
inline static t_nvec	gt__load(t_buffer src, t_size it, t_u64a full)
{
	t_u8			rem;
	t_nvec			wide;

	if (src.mem == nullptr)
		__builtin_unreachable();
	if (__builtin_expect(!full, 0))
	{
		rem = (t_u8)(src.size - it);
		wide = xft_vsplat(' ') & (xft_viota() >= xft_vsplat(rem));
		wide |= xft_vmask_load(src.mem + it, (t_nmask)((1ull << rem) - 1));
		return (wide);
	}
	return (*(t_blknr)(src.mem + it));
}

__attribute__((__nonnull__(3)))
t_result	gt_iterate(t_allocator allocator, t_buffer src,
				t_vec *__restrict__ const vec)
{
	t_size			it;
	t_nvec			wide;
	t_gt_acc		acc;
	t_u64a			full;
	t_carry			c;

	if (src.mem == nullptr)
		__builtin_unreachable();
	acc = (t_gt_acc){.allocator = allocator, .src = src, .state = CODEPOINT};
	c = 0;
	it = 0;
	while (1)
	{
		acc.base = (t_u32)it;
		acc.next = (t_u32)(it + sizeof(t_nvec));
		full = xft_tern(sizeof(t_nvec) <= src.size - it, 1, 0);
		wide = gt__load(src, it, full);
		if (__builtin_expect(gt_classify_and_intern(gt_classify(wide, &c),
					vec, &acc) == KO, 0))
			return (KO);
		if (__builtin_expect(acc.next >= src.size, 0))
			return (OK);
		c = (t_carry)xft_tern(acc.next == it + sizeof(t_nvec), c, 0);
		it = acc.next;
	}
}
