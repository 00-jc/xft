/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove_bench.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 03:11:41 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 10:09:00 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	static t_size			bufsizes[] = {
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20),
		1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2049, (1 << 18), (1 << 20)
	};
	static t_u8				bufalign[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	};
	static t_tailor_bench	benches[] = {
	{ft_memmove_test_varied, (t_blk8r)"memmove_test_varied"},
	{ft_memmove_test_short_aligned, (t_blk8r)"memmove_short_aligned"},
	{ft_memmove_test_short_unaligned, (t_blk8r)"memmove_test_short_unaligned"},
	{ft_memmove_test_medium_aligned, (t_blk8r)"memmove_medium_aligned"},
	{ft_memmove_test_medium_unaligned, (t_blk8r)"memmove_medium_unaligned"},
	{ft_memmove_test_large_aligned, (t_blk8r)"memmove_large_aligned"},
	{ft_memmove_test_large_unaligned, (t_blk8r)"memmove_large_unaligned"},
	};
	t_tailor				t;

	((void)argc, (void)argv, (void)envp, ft_bind_process_to_cpu(0));
	if (!ft_tailor_new(&t, 2, 2000))
		return (1);
	if (!ft_tailor_buffers(&t, bufsizes, bufalign, 28))
		return (1);
	return ((void)ft_tailor_bench(&t, benches, 7), ft_tailor_destroy(&t), 0);
}
