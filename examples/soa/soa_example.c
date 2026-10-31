/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_example.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:16:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "soa_example.h"

//	describes every member of t_particle as a soa column. columns are laid
//	out back to back, so size_of_prev_fields is the running sum of sizes
static t_soa_context	*particle_ctx_new(t_allocator a, t_buffer *buf)
{
	static const t_u32	sizes[FIELDS] = {8, 4, 4, 4, 4};
	static const t_u32	offs[FIELDS] = {__builtin_offsetof(t_particle, id),
		__builtin_offsetof(t_particle, x), __builtin_offsetof(t_particle, y),
		__builtin_offsetof(t_particle, vx), __builtin_offsetof(t_particle, vy)};
	t_soa_context		*ctx;
	t_size				i;

	if (a.vtable == nullptr || a.vtable->allocate == nullptr)
		__builtin_unreachable();
	*buf = a.vtable->allocate(a.allocator, sizeof(t_soa_context)
			+ FIELDS * sizeof(t_soa_field_meta), alignof(t_soa_context));
	if (__builtin_expect(buf->mem == nullptr, 0))
		return (nullptr);
	ctx = (t_soa_context *)buf->mem;
	*ctx = (t_soa_context){.max_alignment = alignof(t_particle),
		.fields_count = FIELDS};
	i = 0;
	while (i < FIELDS)
	{
		ctx->entries[i] = (t_soa_field_meta){.size = sizes[i],
			.offset_from_struct_base = offs[i],
			.size_of_prev_fields = (t_u32)ctx->total_struct_size};
		ctx->total_struct_size += sizes[i++];
	}
	return (ctx);
}

//	soa starts with room for 4, appends grow it and reshuffle the columns
static t_result	particles_fill(t_allocator a, t_soa *soa,
	const t_soa_context *ctx)
{
	t_particle	p;

	while (soa->occupied_elements < PARTICLES)
	{
		p = (t_particle){.id = soa->occupied_elements,
			.vx = (t_i32)soa->occupied_elements, .vy = -1};
		if (__builtin_expect(!xft_soa_append_from_struct(a, soa, &p, ctx), 0))
			return (KO);
	}
	return (OK);
}

//	the soa payoff: each column is a dense array, so the update loop
//	only touches the bytes it needs and vectorizes trivially
static void	particles_step(t_soa *soa, const t_soa_context *ctx,
	t_size steps)
{
	t_i32a *__restrict__ const			x = xft_soa_fields(soa, ctx, 1);
	t_i32a *__restrict__ const			y = xft_soa_fields(soa, ctx, 2);
	const t_i32a *__restrict__ const	vx = xft_soa_fields(soa, ctx, 3);
	const t_i32a *__restrict__ const	vy = xft_soa_fields(soa, ctx, 4);
	t_size								i;

	while (steps--)
	{
		i = 0;
		while (i < soa->occupied_elements)
		{
			x[i] += vx[i];
			y[i] += vy[i];
			++i;
		}
	}
}

static void	particles_print(const t_soa *soa, const t_soa_context *ctx)
{
	static const char	fmt[] = "particle %q at (%d, %d)\n";
	t_u8				out[1024];
	t_writer			w;
	t_u64				values[3];
	t_size				i;

	w = xft_get_fs_writer(xft_fatptr(out, sizeof(out)), xft_get_stdout());
	i = 0;
	while (i < soa->occupied_elements)
	{
		values[0] = ((const t_u64a *)xft_soa_fields(soa, ctx, 0))[i];
		values[1] = (t_u32)((const t_i32a *)xft_soa_fields(soa, ctx, 1))[i];
		values[2] = (t_u32)((const t_i32a *)xft_soa_fields(soa, ctx, 2))[i];
		xft_fmt_writer(&w, xft_fatptr((t_u8 *)fmt, sizeof(fmt) - 1), values);
		++i;
	}
	(void)xft_writer_flush(&w);
}

__attribute__((__nonnull__(1), __noreturn__))
void	xft_main(const t_any *const __restrict__ sp)
{
	t_gpa			gpa;
	t_allocator		a;
	t_buffer		ctx_buf;
	t_soa			soa;
	t_soa_context	*ctx;

	(void)sp;
	gpa = xft_new_gpa();
	a = xft_gpa_allocator(&gpa);
	if (a.vtable == nullptr || a.vtable->free == nullptr
		|| a.vtable->destroy == nullptr)
		__builtin_unreachable();
	ctx = particle_ctx_new(a, &ctx_buf);
	if (__builtin_expect(ctx == nullptr, 0))
		xft_exit_process(1);
	soa = xft_new_soa(a, 4, ctx);
	if (__builtin_expect(soa.ptr == nullptr
			|| !particles_fill(a, &soa, ctx), 0))
		xft_exit_process(1);
	particles_step(&soa, ctx, STEPS);
	particles_print(&soa, ctx);
	xft_destroy_soa(a, &soa);
	a.vtable->free(a.allocator, ctx_buf);
	a.vtable->destroy(a.allocator);
	xft_exit_process(0);
}
