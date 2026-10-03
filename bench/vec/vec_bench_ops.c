/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:46:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:13:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "vec_bench.h"

void	xft_vec_bench_push_back(t_any ptr)
{
	t_allocator	a;
	t_vec		vec;
	t_size		n;
	t_size		bytes;
	t_u64		val;

	a = xft_gpa_allocator(xft_get_bench_vec_gpa());
	vec = xft_new_vec(a, 64, sizeof(t_u64));
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	val = 0;
	while (n-- > 0)
	{
		xft_vec_push_back(a, &vec, (t_u8 *)&val, sizeof(val));
		bytes += sizeof(val);
		val++;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
	xft_vec_destroy(a, &vec);
}

void	xft_vec_bench_push_back_reserved(t_any ptr)
{
	t_allocator	a;
	t_vec		vec;
	t_size		n;
	t_size		needed;
	t_u64		val;

	a = xft_gpa_allocator(xft_get_bench_vec_gpa());
	n = xft_tailor_getcount(ptr);
	needed = n * sizeof(t_u64);
	vec = xft_new_vec(a, needed, sizeof(t_u64));
	val = 0;
	while (n-- > 0)
	{
		xft_vec_push_back(a, &vec, (t_u8 *)&val, sizeof(val));
		val++;
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
	xft_vec_destroy(a, &vec);
}

__attribute__((__nonnull__(1)))
void	xft_vec_bench_push_pop(t_any ptr)
{
	t_allocator	a;
	t_vec		vec;
	t_size		n;
	t_u64		val;

	a = xft_gpa_allocator(xft_get_bench_vec_gpa());
	vec = xft_new_vec(a, 64, sizeof(t_u64));
	n = xft_tailor_getcount(ptr);
	val = 0;
	while (n-- > 0)
	{
		xft_vec_push_back(a, &vec, (t_u8 *)&val, sizeof(val));
		xft_vec_popmv(&vec, &val, sizeof(t_u64));
		__asm__("": "+r,m"(val) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64) * 2);
	xft_vec_destroy(a, &vec);
}
