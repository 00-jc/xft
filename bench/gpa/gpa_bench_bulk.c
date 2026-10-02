/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bench_bulk.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"

#define BULK_BATCH	256

void	xft_gpa_bulk_bench_64(t_any ptr)
{
	static t_buffer	bufs[BULK_BATCH];
	t_gpa			*gpa;
	t_size			n;
	t_size			bytes;
	t_size			i;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n >= BULK_BATCH)
	{
		i = 0;
		while (i < BULK_BATCH)
		{
			bufs[i] = xft_gpa_alloc(gpa, 64, 8);
			bytes += bufs[i++].size;
		}
		i = BULK_BATCH;
		while (i-- > 0)
			xft_gpa_free(gpa, bufs[i]);
		n -= BULK_BATCH;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_gpa_bulk_bench_512(t_any ptr)
{
	static t_buffer	bufs[BULK_BATCH];
	t_gpa			*gpa;
	t_size			n;
	t_size			bytes;
	t_size			i;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n >= BULK_BATCH)
	{
		i = 0;
		while (i < BULK_BATCH)
		{
			bufs[i] = xft_gpa_alloc(gpa, 512, 8);
			bytes += bufs[i++].size;
		}
		i = BULK_BATCH;
		while (i-- > 0)
			xft_gpa_free(gpa, bufs[i]);
		n -= BULK_BATCH;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_gpa_bulk_bench_mixed(t_any ptr)
{
	static t_buffer	bufs[BULK_BATCH];
	t_gpa			*gpa;
	t_size			n;
	t_size			bytes;
	t_size			i;

	gpa = xft_get_bench_gpa();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n >= BULK_BATCH)
	{
		i = 0;
		while (i < BULK_BATCH)
		{
			bufs[i] = xft_gpa_alloc(gpa, (t_size)8 << ((i & 3) * 3), 8);
			bytes += bufs[i++].size;
		}
		i = BULK_BATCH;
		while (i-- > 0)
			xft_gpa_free(gpa, bufs[i]);
		n -= BULK_BATCH;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}
