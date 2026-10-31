/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_test_ctx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 16:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/soa/soa_test.h"

static void	soa_test_set_field(t_soa_context *ctx, t_size idx,
	t_u32 size, t_u32 offset)
{
	ctx->entries[idx].size = size;
	ctx->entries[idx].offset_from_struct_base = offset;
	ctx->entries[idx].size_of_prev_fields = 0;
	if (idx > 0)
		ctx->entries[idx].size_of_prev_fields
			= ctx->entries[idx - 1].size_of_prev_fields
			+ ctx->entries[idx - 1].size;
	ctx->total_struct_size += size;
}

t_buffer	soa_test_ctx_new(t_allocator a)
{
	t_buffer		buf;
	t_soa_context	*ctx;

	buf = a.vtable->allocate(a.allocator, sizeof(t_soa_context)
			+ SOA_TEST_FIELDS * sizeof(t_soa_field_meta), SOA_TEST_ALIGN);
	xft_pin_invariant(buf.mem != nullptr);
	ctx = (t_soa_context *)buf.mem;
	*ctx = (t_soa_context){.max_alignment = SOA_TEST_ALIGN,
		.fields_count = SOA_TEST_FIELDS};
	soa_test_set_field(ctx, 0, sizeof(t_u8),
		__builtin_offsetof(t_soa_test_elem, tag));
	soa_test_set_field(ctx, 1, sizeof(t_u64),
		__builtin_offsetof(t_soa_test_elem, id));
	soa_test_set_field(ctx, 2, sizeof(t_u32),
		__builtin_offsetof(t_soa_test_elem, val));
	soa_test_set_field(ctx, 3, sizeof(t_u16),
		__builtin_offsetof(t_soa_test_elem, small));
	return (buf);
}

__attribute__((const))
t_soa_test_elem	soa_test_make(t_size i)
{
	return ((t_soa_test_elem){
		.tag = (t_u8)(i * 7),
		.id = (i * 0x9E3779B97F4A7C15ULL) ^ 0xA5A5A5A5A5A5A5A5ULL,
		.val = (t_u32)(i * 2654435761U),
		.small = (t_u16)(i ^ 0xBEEF)});
}

void	soa_test_check(const t_soa *soa, const t_soa_context *ctx, t_size i)
{
	const t_soa_test_elem	want = soa_test_make(i);
	const t_u8				*tags = xft_soa_fields(soa, ctx, 0);
	const t_u64				*ids = xft_soa_fields(soa, ctx, 1);
	const t_u32				*vals = xft_soa_fields(soa, ctx, 2);
	const t_u16				*smalls = xft_soa_fields(soa, ctx, 3);

	xft_pin_invariant(tags[i] == want.tag);
	xft_pin_invariant(ids[i] == want.id);
	xft_pin_invariant(vals[i] == want.val);
	xft_pin_invariant(smalls[i] == want.small);
}

void	soa_test_check_aligned(const t_soa *soa, const t_soa_context *ctx)
{
	t_size	it;

	xft_pin_invariant(soa->capacity_elements % ctx->max_alignment == 0);
	it = 0;
	while (it < ctx->fields_count)
	{
		xft_pin_invariant(((t_uptr)xft_soa_fields(soa, ctx, it)
				& (ctx->max_alignment - 1)) == 0);
		++it;
	}
}
