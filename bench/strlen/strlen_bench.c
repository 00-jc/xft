/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_bench.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 01:33:46 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/08 01:33:46 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "cstr_bench.h"

__attribute__((__always_inline__))
inline void	ft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{ft_strlen_test_varied, (t_blk8r)"strlen_varied"},
	{ft_strlen_test_short_aligned, (t_blk8r)"strlen_short_aligned"},
	{ft_strlen_test_short_unaligned, (t_blk8r)"strlen_short_unaligned"},
	{ft_strlen_test_medium_aligned, (t_blk8r)"strlen_medium_aligned"},
	{ft_strlen_test_medium_unaligned, (t_blk8r)"strlen_medium_unaligned"},
	{ft_strlen_test_large_aligned, (t_blk8r)"strlen_large_aligned"},
	{ft_strlen_test_large_unaligned, (t_blk8r)"strlen_large_unaligned"},
	};
	t_tailor				t;

	((void)sp, ft_bind_process_to_cpu(0));
	if (!ft_tailor_new(&t, 2, 2000))
		ft_exit(1);
	if (!ft_strlen_bench_buffers(&t))
		ft_exit(1);
	((void)ft_tailor_bench(&t, benches, 7), ft_tailor_destroy(&t), ft_exit(0));
}
