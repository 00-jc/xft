/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_bench.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 15:14:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 11:39:45 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "mem_bench.h"
#include <xft/rt.h>
#include "bench.h"

static void	memcpy_bench_exclusive(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_memcpy_test_varied, "xft_memcpy_varied", "memcpy_varied"},
	{xft_memcpy_test_large_aligned, "xft_memcpy_large_aligned",
		"memcpy_large_aligned"},
	{xft_memcpy_test_large_unaligned, "xft_memcpy_large_unaligned",
		"memcpy_large_unaligned"},
	};

	(void)xft_tailor_bench_exclusive(t, benches,
		sizeof(benches) / sizeof(*benches));
}

static void	memcpy_bench_queue(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_memcpy_test_short_aligned, "xft_memcpy_short_aligned",
		"memcpy_short_aligned"},
	{xft_memcpy_test_short_unaligned, "xft_memcpy_short_unaligned",
		"memcpy_short_unaligned"},
	{xft_memcpy_test_medium_aligned, "xft_memcpy_medium_aligned",
		"memcpy_medium_aligned"},
	{xft_memcpy_test_medium_unaligned, "xft_memcpy_medium_unaligned",
		"memcpy_medium_unaligned"},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
	memcpy_bench_exclusive(t);
}

void	xft_bench_memcpy(t_tailor *t)
{
	static t_size			bufsizes[] = {
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
	};
	static t_u8				bufalign[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	};

	if (!xft_tailor_buffers(t, bufsizes, bufalign,
			sizeof(bufsizes) / sizeof(*bufsizes)))
		xft_exit_process(1);
	memcpy_bench_queue(t);
}
