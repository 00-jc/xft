/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soa_bench_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 18:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 16:33:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "soa_bench.h"

static t_u64	soa_bench_sum(const t_u64a *__restrict__ col)
{
	t_u64	sum;
	t_size	i;

	sum = 0;
	i = 0;
	while (i < SOA_BENCH_FILL)
		sum += col[i++];
	return (sum);
}

__attribute__((__nonnull__(1)))
void	xft_soa_bench_read(t_any ptr)
{
	const t_soa_context		*ctx = xft_get_bench_soa_ctx();
	const t_allocator		a = xft_gpa_allocator(xft_get_bench_soa_gpa());
	t_soa					soa;
	t_size					n;
	t_size					i;

	soa = xft_soa_bench_filled(a);
	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		i = xft_tailor_get_random_num(ptr) % SOA_BENCH_FILL;
		xft_pin_invariant(((const t_u64a *)xft_soa_fields(&soa, ctx, 0))[i]
			== i);
		xft_pin_invariant(((const t_i32a *)xft_soa_fields(&soa, ctx, 4))[i]
			== -1);
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * (sizeof(t_u64) + sizeof(t_i32)));
	xft_destroy_soa(a, &soa);
}

__attribute__((__nonnull__(1)))
void	xft_soa_bench_column_sum(t_any ptr)
{
	const t_soa_context		*ctx = xft_get_bench_soa_ctx();
	const t_allocator		a = xft_gpa_allocator(xft_get_bench_soa_gpa());
	t_soa					soa;
	t_size					n;
	t_u64					sum;

	soa = xft_soa_bench_filled(a);
	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
	{
		sum = soa_bench_sum(xft_soa_fields(&soa, ctx, 0));
		__asm__("" : : "r"(sum), "r"(soa.ptr) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * SOA_BENCH_FILL * sizeof(t_u64));
	xft_destroy_soa(a, &soa);
}
