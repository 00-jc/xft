/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bench_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"

void	xft_gpa_bench_8(t_any ptr)
{
	t_gpa		*gpa;
	t_size		n;
	t_size		bytes;
	t_buffer	b;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = xft_gpa_alloc(gpa, 8, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		xft_gpa_free(gpa, b);
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_gpa_bench_64(t_any ptr)
{
	t_gpa		*gpa;
	t_size		n;
	t_size		bytes;
	t_buffer	b;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = xft_gpa_alloc(gpa, 64, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		xft_gpa_free(gpa, b);
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_gpa_bench_512(t_any ptr)
{
	t_gpa		*gpa;
	t_size		n;
	t_size		bytes;
	t_buffer	b;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = xft_gpa_alloc(gpa, 512, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		xft_gpa_free(gpa, b);
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_gpa_bench_8k(t_any ptr)
{
	t_gpa		*gpa;
	t_size		n;
	t_size		bytes;
	t_buffer	b;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = xft_gpa_alloc(gpa, 8192, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		xft_gpa_free(gpa, b);
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_gpa_bench_varied(t_any ptr)
{
	static const t_size	sizes[4] = {8, 64, 512, 4096};
	t_gpa				*gpa;
	t_size				n;
	t_size				bytes;
	t_buffer			b;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		b = xft_gpa_alloc(gpa, sizes[n & 3], 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		xft_gpa_free(gpa, b);
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}
