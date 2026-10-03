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

#include "tailor.h"
#include "mem_bench.h"

__attribute__((__always_inline__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	static t_size			bufsizes[] = {
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
	};
	static t_u8				bufalign[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	};
	static t_tailor_bench	benches[] = {
	{xft_memcpy_test_varied, (t_blk8r)"memcpy_test_varied"},
	{xft_memcpy_test_short_aligned, (t_blk8r)"memcpy_short_aligned"},
	{xft_memcpy_test_short_unaligned, (t_blk8r)"memcpy_test_short_unaligned"},
	{xft_memcpy_test_medium_aligned, (t_blk8r)"memcpy_medium_aligned"},
	{xft_memcpy_test_medium_unaligned, (t_blk8r)"memcpy_medium_unaligned"},
	{xft_memcpy_test_large_aligned, (t_blk8r)"memcpy_large_aligned"},
	{xft_memcpy_test_large_unaligned, (t_blk8r)"memcpy_large_unaligned"},
	};
	t_tailor				t;

	((void)sp, xft_bind_process_to_cpu(0));
	if (!xft_new_tailor(&t, 2, 2000)
		|| !xft_tailor_buffers(&t, bufsizes, bufalign, 28))
		xft_exit(1);
	((void)xft_tailor_bench(&t, benches, 7),
		xft_tailor_destroy(&t), xft_exit(0));
}
