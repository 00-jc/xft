/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_bench_iter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:33:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "soa_bench.h"

static void	soa_bench_step(t_i32a *__restrict__ x, t_i32a *__restrict__ y,
	const t_i32a *__restrict__ vx, const t_i32a *__restrict__ vy)
{
	t_size	i;

	i = 0;
	while (i < SOA_BENCH_FILL)
	{
		x[i] += vx[i];
		y[i] += vy[i];
		++i;
	}
}

static void	aos_bench_step(t_soa_bench_particle *__restrict__ p)
{
	t_size	i;

	i = 0;
	while (i < SOA_BENCH_FILL)
	{
		p[i].x += p[i].vx;
		p[i].y += p[i].vy;
		++i;
	}
}

__attribute__((__nonnull__(1)))
void	xft_soa_bench_update(t_any ptr)
{
	const t_soa_context		*ctx = xft_get_bench_soa_ctx();
	const t_allocator		a = xft_gpa_allocator(xft_get_bench_soa_gpa());
	t_soa					soa;
	t_size					n;

	soa = xft_soa_bench_filled(a);
	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		soa_bench_step(xft_soa_fields(&soa, ctx, 1),
			xft_soa_fields(&soa, ctx, 2), xft_soa_fields(&soa, ctx, 3),
			xft_soa_fields(&soa, ctx, 4));
		__asm__("" : : "r"(soa.ptr) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr, xft_tailor_getcount(ptr)
		* SOA_BENCH_FILL * 4 * sizeof(t_i32));
	xft_destroy_soa(a, &soa);
}

__attribute__((__nonnull__(1)))
void	xft_soa_bench_aos_update(t_any ptr)
{
	const t_allocator		a = xft_gpa_allocator(xft_get_bench_soa_gpa());
	t_buffer				buf;
	t_soa_bench_particle	*p;
	t_size					n;

	if (a.vtable == nullptr || a.vtable->allocate == nullptr
		|| a.vtable->free == nullptr)
		__builtin_unreachable();
	buf = a.vtable->allocate(a.allocator,
			SOA_BENCH_FILL * sizeof(t_soa_bench_particle),
			alignof(t_soa_bench_particle));
	p = (t_soa_bench_particle *)buf.mem;
	xft_pin_invariant(p != nullptr);
	n = SOA_BENCH_FILL;
	while (n-- > 0)
		p[n] = xft_soa_bench_make(n);
	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		aos_bench_step(p);
		__asm__("" : : "r"(p) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr, xft_tailor_getcount(ptr)
		* SOA_BENCH_FILL * 4 * sizeof(t_i32));
	a.vtable->free(a.allocator, buf);
}
