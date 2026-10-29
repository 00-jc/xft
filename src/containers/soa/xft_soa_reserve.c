/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_soa_reserve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 14:03:23 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/16 00:09:27 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/soa.h>

__attribute__((__always_inline__, __unused__))
static inline void	xft__soa_reposition(
	t_soa *__restrict__ const soa,
	const t_soa_context *__restrict__ const ctx,
	t_size	new_size)
{
	t_size							it;
	t_size							old_offset;
	t_size							new_offset;
	t_size							elem_size;
	const t_u8 *const				base = soa->ptr;

	if (ctx->fields_count == 0)
		__builtin_unreachable();
	it = ctx->fields_count;
	while (it--)
	{
		elem_size = ctx->entries[it].size;
		old_offset = soa->capacity_elements
			* ctx->entries[it].size_of_prev_fields;
		new_offset = new_size * ctx->entries[it].size_of_prev_fields;
		xft_memmove((t_any)(base + new_offset), (t_any)(base + old_offset),
			soa->occupied_elements * elem_size);
	}
}

__attribute__((__nonnull__(2, 3)))
t_result	xft_soa_reserve(t_allocator allocator,
	t_soa *__restrict__ const soa,
	const t_soa_context *__restrict__ const ctx,
	t_size elements_to_reserve)
{
	t_buffer	new_buffer;
	t_size		new_size;
	t_size		usable;

	if (allocator.allocator == nullptr || allocator.vtable.realloc == nullptr)
		__builtin_unreachable();
	if (soa->capacity_elements - soa->occupied_elements >= elements_to_reserve)
		return (OK);
	new_size = xft_max_s(soa->capacity_elements << 1,
			soa->occupied_elements + elements_to_reserve);
	new_size = (new_size + ctx->max_alignment - 1) & ~(ctx->max_alignment - 1);
	new_buffer = allocator.vtable.realloc(allocator.allocator,
			xft_fatptr(soa->ptr, soa->allocator_bytes_given),
			new_size * ctx->total_struct_size,
			xft_max_s(ctx->max_alignment, __GCC_CONSTRUCTIVE_SIZE));
	if (__builtin_expect(new_buffer.mem == nullptr, 0))
		return (KO);
	soa->ptr = new_buffer.mem;
	usable = (new_buffer.size / ctx->total_struct_size)
		& ~(ctx->max_alignment - 1);
	new_size = xft_tern_s(usable > new_size, usable, new_size);
	xft__soa_reposition(soa, ctx, new_size);
	soa->capacity_elements = new_size;
	soa->allocator_bytes_given = new_buffer.size;
	return (OK);
}
