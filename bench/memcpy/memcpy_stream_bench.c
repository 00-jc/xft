/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_stream_bench.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 11:40:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "mem_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_memcpy_stream(t_tailor *t)
{
	static t_size			bufsizes[] = {
		XFT_LLC + 1, XFT_LLC + 1,
		XFT_LLC * 2, XFT_LLC * 2,
		XFT_LLC + 1, XFT_LLC + 1,
		XFT_LLC * 2, XFT_LLC * 2,
	};
	static t_u8				bufalign[] = {
		1, 1, 1, 1,
		64, 64, 64, 64,
	};
	static t_tailor_bench	benches[] = {
	{xft_memcpy_test_stream_1x_unaligned, "memcpy_stream_1x_unalign", nullptr},
	{xft_memcpy_test_stream_2x_unaligned, "memcpy_stream_2x_unalign", nullptr},
	{xft_memcpy_test_stream_1x_aligned, "memcpy_stream_1x_aligned", nullptr},
	{xft_memcpy_test_stream_2x_aligned, "memcpy_stream_2x_aligned", nullptr},
	};

	if (!xft_tailor_buffers(t, bufsizes, bufalign,
			sizeof(bufsizes) / sizeof(*bufsizes)))
		xft_exit_process(1);
	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
