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
inline void	xft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{xft_strlen_test_varied, (t_blk8r)"strlen_varied"},
	{xft_strlen_test_short_aligned, (t_blk8r)"strlen_short_aligned"},
	{xft_strlen_test_short_unaligned, (t_blk8r)"strlen_short_unaligned"},
	{xft_strlen_test_medium_aligned, (t_blk8r)"strlen_medium_aligned"},
	{xft_strlen_test_medium_unaligned, (t_blk8r)"strlen_medium_unaligned"},
	{xft_strlen_test_large_aligned, (t_blk8r)"strlen_large_aligned"},
	{xft_strlen_test_large_unaligned, (t_blk8r)"strlen_large_unaligned"},
	};
	t_tailor				t;

	((void)sp, xft_bind_process_to_cpu(0));
	if (!xft_new_tailor(&t, 2, 2000))
		xft_exit(1);
	if (!xft_strlen_bench_buffers(&t))
		xft_exit(1);
	((void)xft_tailor_bench(&t, benches, 7),
		xft_tailor_destroy(&t), xft_exit(0));
}
