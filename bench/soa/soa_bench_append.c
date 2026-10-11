/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_bench_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 18:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "soa_bench.h"

__attribute__((__nonnull__(1)))
void	xft_soa_bench_append(t_any ptr)
{
	const t_soa_context		*ctx = xft_get_bench_soa_ctx();
	t_allocator				a;
	t_soa					soa;
	t_soa_bench_particle	p;
	t_size					n;

	a = xft_gpa_allocator(xft_get_bench_soa_gpa());
	soa = xft_new_soa(a, 64, ctx);
	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		p = xft_soa_bench_make(n);
		xft_pin_invariant(xft_soa_append_from_struct(a, &soa, &p, ctx));
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * ctx->total_struct_size);
	xft_destroy_soa(a, &soa);
}

__attribute__((__nonnull__(1)))
void	xft_soa_bench_append_reserved(t_any ptr)
{
	const t_soa_context		*ctx = xft_get_bench_soa_ctx();
	t_allocator				a;
	t_soa					soa;
	t_soa_bench_particle	p;
	t_size					n;

	a = xft_gpa_allocator(xft_get_bench_soa_gpa());
	n = xft_tailor_getcount(ptr);
	soa = xft_new_soa(a, n, ctx);
	while (n-- > 0)
	{
		p = xft_soa_bench_make(n);
		xft_pin_invariant(xft_soa_append_from_struct(a, &soa, &p, ctx));
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * ctx->total_struct_size);
	xft_destroy_soa(a, &soa);
}

__attribute__((__nonnull__(1)))
void	xft_soa_bench_append_unchecked(t_any ptr)
{
	const t_soa_context		*ctx = xft_get_bench_soa_ctx();
	t_allocator				a;
	t_soa					soa;
	t_soa_bench_particle	p;
	t_size					n;

	a = xft_gpa_allocator(xft_get_bench_soa_gpa());
	n = xft_tailor_getcount(ptr);
	soa = xft_new_soa(a, n, ctx);
	xft_pin_invariant(soa.ptr != nullptr);
	while (n-- > 0)
	{
		p = xft_soa_bench_make(n);
		xft_soa_append_from_struct_unchecked(&soa, &p, ctx);
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * ctx->total_struct_size);
	xft_destroy_soa(a, &soa);
}
