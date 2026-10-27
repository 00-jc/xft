/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_bench_state.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:33:55 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "soa_bench.h"

t_gpa	*xft_get_bench_soa_gpa(void)
{
	static t_gpa	gpa = {0};

	if (gpa.slab == nullptr)
		gpa = xft_new_gpa();
	return (&gpa);
}

static void	soa_bench_set_field(t_soa_context *ctx, t_size idx,
	t_u32 size, t_u32 offset)
{
	ctx->entries[idx] = (t_soa_field_meta){.size = size,
		.offset_from_struct_base = offset,
		.size_of_prev_fields = (t_u32)ctx->total_struct_size};
	ctx->total_struct_size += size;
}

const t_soa_context	*xft_get_bench_soa_ctx(void)
{
	static t_soa_context	*ctx = nullptr;
	t_allocator				a;

	if (ctx != nullptr)
		return (ctx);
	a = xft_gpa_allocator(xft_get_bench_soa_gpa());
	ctx = (t_soa_context *)a.vtable.allocate(a.allocator,
			sizeof(t_soa_context) + SOA_BENCH_FIELDS
			* sizeof(t_soa_field_meta), alignof(t_soa_context)).mem;
	xft_pin_invariant(ctx != nullptr);
	*ctx = (t_soa_context){.max_alignment = alignof(t_soa_bench_particle),
		.fields_count = SOA_BENCH_FIELDS};
	soa_bench_set_field(ctx, 0, 8, __builtin_offsetof(t_soa_bench_particle,
			id));
	soa_bench_set_field(ctx, 1, 4, __builtin_offsetof(t_soa_bench_particle,
			x));
	soa_bench_set_field(ctx, 2, 4, __builtin_offsetof(t_soa_bench_particle,
			y));
	soa_bench_set_field(ctx, 3, 4, __builtin_offsetof(t_soa_bench_particle,
			vx));
	soa_bench_set_field(ctx, 4, 4, __builtin_offsetof(t_soa_bench_particle,
			vy));
	return (ctx);
}

__attribute__((const))
t_soa_bench_particle	xft_soa_bench_make(t_size i)
{
	return ((t_soa_bench_particle){.id = i, .x = (t_i32)i, .y = -(t_i32)i,
		.vx = (t_i32)(i & 7), .vy = -1});
}

t_soa	xft_soa_bench_filled(t_allocator a)
{
	const t_soa_context		*ctx = xft_get_bench_soa_ctx();
	t_soa					soa;
	t_soa_bench_particle	p;

	soa = xft_new_soa(a, SOA_BENCH_FILL, ctx);
	xft_pin_invariant(soa.ptr != nullptr);
	while (soa.occupied_elements < SOA_BENCH_FILL)
	{
		p = xft_soa_bench_make(soa.occupied_elements);
		xft_soa_append_from_struct_unchecked(&soa, &p, ctx);
	}
	return (soa);
}
