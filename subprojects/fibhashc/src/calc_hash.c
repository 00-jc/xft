/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 23:07:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/19 23:24:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fibhashc.h"

__attribute__((__nonnull__(2)))
t_result	get_hash(t_allocator allocator,
	t_writer *writer, t_buffer src)
{
	t_vec		nums;
	t_u64a		and;
	t_u64a		or;
	t_size		it;

	nums = fhc_run_pipeline(allocator, src);
	if (__builtin_expect(nums.buf.mem == nullptr, 0))
		return (KO);
	it = 0;
	and = ~0;
	or = 0;
	while (it < xft_vec_len(&nums, sizeof(t_u64a)))
	{
		and &= *(t_blk64r)xft_vec_get(&nums, it, sizeof(t_u64a));
		or |= *(t_blk64r)xft_vec_get(&nums, it++, sizeof(t_u64a));
	}
	and ^= or;
	xft_fmt_writer(writer, xft_fatptr((t_any)"%X\n", sizeof("%x\n") - 1), &and);
	xft_writer_flush(writer);
	xft_vec_destroy(allocator, &nums);
	return (OK);
}
