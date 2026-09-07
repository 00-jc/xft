/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_bench_run.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:34:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:34:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "libc_bench.h"

void	ft_libc_bench_memcpy(t_tailor *t)
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
	{ft_libc_memcpy_varied, (t_blk8r)"libc_memcpy_varied"},
	{ft_libc_memcpy_short_aligned, (t_blk8r)"libc_memcpy_short_aligned"},
	{ft_libc_memcpy_short_unaligned, (t_blk8r)"libc_memcpy_short_unaligned"},
	{ft_libc_memcpy_medium_aligned, (t_blk8r)"libc_memcpy_medium_aligned"},
	{ft_libc_memcpy_medium_unaligned, (t_blk8r)"libc_memcpy_medium_unaligned"},
	{ft_libc_memcpy_large_aligned, (t_blk8r)"libc_memcpy_large_aligned"},
	{ft_libc_memcpy_large_unaligned, (t_blk8r)"libc_memcpy_large_unaligned"},
	};

	if (!ft_tailor_buffers(t, bufsizes, bufalign, 28))
		ft_exit(1);
	(void)ft_tailor_bench(t, benches, 7);
}

void	ft_libc_bench_strlen(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{ft_libc_strlen_varied, (t_blk8r)"libc_strlen_varied"},
	{ft_libc_strlen_short_aligned, (t_blk8r)"libc_strlen_short_aligned"},
	{ft_libc_strlen_short_unaligned, (t_blk8r)"libc_strlen_short_unaligned"},
	{ft_libc_strlen_medium_aligned, (t_blk8r)"libc_strlen_medium_aligned"},
	{ft_libc_strlen_medium_unaligned, (t_blk8r)"libc_strlen_medium_unaligned"},
	{ft_libc_strlen_large_aligned, (t_blk8r)"libc_strlen_large_aligned"},
	{ft_libc_strlen_large_unaligned, (t_blk8r)"libc_strlen_large_unaligned"},
	};

	if (!ft_strlen_bench_buffers(t))
		ft_exit(1);
	(void)ft_tailor_bench(t, benches, 7);
}
