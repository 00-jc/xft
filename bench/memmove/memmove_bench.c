/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_bench.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 03:11:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 11:38:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "mem_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_memmove(t_tailor *t)
{
	static t_size			bufsizes[] = {
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20)
	};
	static t_u8				bufalign[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	};
	static t_tailor_bench	benches[] = {
	{xft_memmove_test_varied, "memmove_test_varied", nullptr},
	{xft_memmove_test_short_aligned, "memmove_short_aligned", nullptr},
	{xft_memmove_test_short_unaligned, "memmove_test_short_unaligned", nullptr},
	{xft_memmove_test_medium_aligned, "memmove_medium_aligned", nullptr},
	{xft_memmove_test_medium_unaligned, "memmove_medium_unaligned", nullptr},
	{xft_memmove_test_large_aligned, "memmove_large_aligned", nullptr},
	{xft_memmove_test_large_unaligned, "memmove_large_unaligned", nullptr},
	};

	if (!xft_tailor_buffers(t, bufsizes, bufalign,
			sizeof(bufsizes) / sizeof(*bufsizes)))
		xft_exit_process(1);
	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
