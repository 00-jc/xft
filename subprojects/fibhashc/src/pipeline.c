/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:46:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/19 23:14:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fibhashc.h"
#include "vec.h"

__attribute__((const, __always_inline__, __flatten__))
inline static t_src_span	fhc__calc_span(t_u64 mask)
{
	t_u32a		start;

	start = (t_u32a)xft_memctz_u64(mask);
	return ((t_src_span){
		.start = start,
		.len = (t_u32a)xft_memctz_u64(~(mask >> start)),
	});
}

__attribute__((__nonnull__(1, 2), __always_inline__))
inline static void	fhc__carry_run(t_vec *store,
	const t_fhc_cursor *cur,
	t_u64 mask)
{
	t_u64a	*last;

	last = xft_vec_get_last(store, sizeof(t_u64a));
	*last = fhc_load_span(cur->run, (t_u32)(cur->pos - cur->run)
			+ (t_u32)xft_memctz_u64(~mask));
}

__attribute__((__nonnull__(2, 3), __flatten__, __always_inline__))
inline static t_result	fhc__emit_nums(t_allocator allocator,
	t_vec *store,
	t_fhc_cursor *cur,
	t_nmask mask)
{
	t_src_span	sp;
	t_u64a		num;

	while (mask != 0)
	{
		sp = fhc__calc_span(mask);
		cur->run = cur->pos + sp.start;
		num = fhc_load_span(cur->run, sp.len);
		if (__builtin_expect(sp.len > 8, 0))
			return (KO);
		if (__builtin_expect(!xft_vec_push_back(allocator, store,
					(t_any) & num, sizeof(t_u64a)), 0))
			return (KO);
		mask &= mask + (mask & -mask);
	}
	return (OK);
}

__attribute__((__nonnull__(3, 4), __flatten__, __always_inline__))
inline static t_result	fhc_tokenize(t_allocator allocator,
	t_buffer src,
	t_vec *store,
	t_fhc_cursor *cur)
{
	t_nvec		vec;
	t_nmask		mask;
	t_size		left;
	t_u8		carried;
	t_result	res;

	if (src.mem == nullptr || cur->pos >= src.mem + src.size)
		__builtin_unreachable();
	left = (t_size)(src.mem + src.size - cur->pos);
	mask = -1;
	mask &= xft_tern(left < sizeof(t_nvec), (1ULL << left) - 1, ~0ULL);
	vec = xft_vmask_load(cur->pos, mask);
	mask &= ~(xft_veqmask(vec, ' ') | xft_veqmask(vec, '\r')
			| xft_veqmask(vec, '\t') | xft_veqmask(vec, '\n'));
	carried = cur->open_run;
	cur->open_run = mask >> (sizeof(t_nvec) - 1);
	if (carried && (mask & 1))
	{
		fhc__carry_run(store, cur, mask);
		mask &= mask + 1;
	}
	res = fhc__emit_nums(allocator, store, cur, mask);
	cur->pos += sizeof(t_nvec);
	return (res);
}

t_vec	fhc_run_pipeline(t_allocator allocator,
	t_buffer src)
{
	t_vec			nums;
	t_fhc_cursor	cur;

	nums = xft_new_vec(allocator, 32, sizeof(t_u64a));
	cur.pos = src.mem;
	cur.run = src.mem;
	cur.open_run = 0;
	while (nums.buf.mem != nullptr && cur.pos < src.mem + src.size)
	{
		if (__builtin_expect(
				fhc_tokenize(allocator, src, &nums, &cur) == KO, 0))
			xft_vec_destroy(allocator, &nums);
	}
	return (nums);
}
