/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_soa_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 00:20:02 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/16 00:19:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/soa.h>

__attribute__((__always_inline__, __nonnull__(1, 2, 3), __used__))
inline void	xft_soa_append_from_struct_unchecked(
	t_soa *__restrict__ const soa,
	t_any __restrict__ const _struct,
	const t_soa_context *__restrict__ const ctx)
{
	t_size							it;
	t_any							start;
	t_size							off;
	t_size							acc;
	const t_u8 *__restrict__ const	base = soa->ptr;

	it = 0;
	acc = 0;
	while (it < ctx->fields_count)
	{
		off = ctx->entries[it].offset_from_struct_base;
		start = (t_any)(base + acc + soa->occupied_elements
				* ctx->entries[it].size);
		xft_memcpy(start, (t_blk8r)_struct + off, ctx->entries[it].size);
		acc += soa->capacity_elements * ctx->entries[it].size;
		++it;
	}
	++soa->occupied_elements;
}

__attribute__((__nonnull__(2, 3, 4), __always_inline__, __used__))
inline t_result	xft_soa_append_from_struct(
	t_allocator allocator,
	t_soa *__restrict__ const soa,
	t_any __restrict__ const _struct,
	const t_soa_context *__restrict__ const ctx)
{
	if (__builtin_expect(soa->occupied_elements == soa->capacity_elements
			&& !xft_soa_reserve(allocator, soa, ctx, 1), 0))
		return (KO);
	xft_soa_append_from_struct_unchecked(soa, _struct, ctx);
	return (OK);
}
