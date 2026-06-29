/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_stream_bench.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/19 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "mem_bench.h"

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	static t_size			bufsizes[] = {
		FT_LLC + 1, FT_LLC + 1,
		FT_LLC * 2, FT_LLC * 2,
		FT_LLC + 1, FT_LLC + 1,
		FT_LLC * 2, FT_LLC * 2,
	};
	static t_u8				bufalign[] = {
		1, 1, 1, 1,
		64, 64, 64, 64,
	};
	static t_tailor_bench	benches[] = {
	{ft_memcpy_test_stream_1x_unaligned, (t_blk8r)"memcpy_stream_1x_unaligned"},
	{ft_memcpy_test_stream_2x_unaligned, (t_blk8r)"memcpy_stream_2x_unaligned"},
	{ft_memcpy_test_stream_1x_aligned, (t_blk8r)"memcpy_stream_1x_aligned"},
	{ft_memcpy_test_stream_2x_aligned, (t_blk8r)"memcpy_stream_2x_aligned"},
	};
	t_tailor				t;

	(void)argc;
	(void)argv;
	(void)envp;
	ft_bind_process_to_cpu(0);
	if (!ft_tailor_new(&t, 2, 2000))
		return (1);
	if (!ft_tailor_buffers(&t, bufsizes, bufalign, 8))
		return (1);
	return ((void)ft_tailor_bench(&t, benches, 4), ft_tailor_destroy(&t), 0);
}
