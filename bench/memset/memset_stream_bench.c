/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_stream_bench.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/13 11:40:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

__attribute__((__always_inline__))
inline void	xft_main(const t_any *__restrict__ const sp)
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
	{xft_memset_test_stream_1x_unaligned, (t_blk8r)"memset_stream_1x_unalign"},
	{xft_memset_test_stream_2x_unaligned, (t_blk8r)"memset_stream_2x_unalign"},
	{xft_memset_test_stream_1x_aligned, (t_blk8r)"memset_stream_1x_aligned"},
	{xft_memset_test_stream_2x_aligned, (t_blk8r)"memset_stream_2x_aligned"},
	};
	t_tailor				t;

	((void)sp, xft_bind_process_to_cpu(0));
	if (!xft_tailor_new(&t, 2, 2000)
		|| !xft_tailor_buffers(&t, bufsizes, bufalign, 8))
		xft_exit(1);
	((void)xft_tailor_bench(&t, benches, 4),
		xft_tailor_destroy(&t), xft_exit(0));
}
