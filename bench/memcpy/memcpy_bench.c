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
inline void	ft_main(const t_any *__restrict__ const sp)
{
	static t_size			bufsizes[] = {
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
	};
	static t_u8				bufalign[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	};
	static t_tailor_bench	benches[] = {
	{ft_memcpy_test_varied, (t_blk8r)"memcpy_test_varied"},
	{ft_memcpy_test_short_aligned, (t_blk8r)"memcpy_short_aligned"},
	{ft_memcpy_test_short_unaligned, (t_blk8r)"memcpy_test_short_unaligned"},
	{ft_memcpy_test_medium_aligned, (t_blk8r)"memcpy_medium_aligned"},
	{ft_memcpy_test_medium_unaligned, (t_blk8r)"memcpy_medium_unaligned"},
	{ft_memcpy_test_large_aligned, (t_blk8r)"memcpy_large_aligned"},
	{ft_memcpy_test_large_unaligned, (t_blk8r)"memcpy_large_unaligned"},
	};
	t_tailor				t;

	((void)sp, ft_bind_process_to_cpu(0));
	if (!ft_tailor_new(&t, 2, 2000))
		ft_exit(1);
	if (!ft_tailor_buffers(&t, bufsizes, bufalign, 28))
		ft_exit(1);
	((void)ft_tailor_bench(&t, benches, 7), ft_tailor_destroy(&t), ft_exit(0));
}
