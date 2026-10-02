/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bench_rand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"

void	xft_gpa_bench_random(t_any ptr)
{
	t_gpa		*gpa;
	t_size		n;
	t_size		bytes;
	t_size		sz;
	t_buffer	b;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		sz = 8ULL << (xft_tailor_get_random_num(ptr) % 14);
		b = xft_gpa_alloc(gpa, sz, 8);
		__asm__("": "+r,m"(b.mem) ::"memory");
		bytes += b.size;
		xft_gpa_free(gpa, b);
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}
