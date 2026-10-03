/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:40:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"
#include "rt.h"

__attribute__((__always_inline__))
inline void	xft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{xft_arena_bench_8, (t_blk8r)"arena_alloc_8"},
	{xft_arena_bench_64, (t_blk8r)"arena_alloc_64"},
	{xft_arena_bench_512, (t_blk8r)"arena_alloc_512"},
	{xft_arena_bench_varied, (t_blk8r)"arena_alloc_varied"},
	{xft_arena_bench_random, (t_blk8r)"arena_alloc_random"},
	};
	t_tailor				t;

	(void)sp;
	xft_bind_process_to_cpu(0);
	if (!xft_new_tailor(&t, 2, 2000))
		xft_exit(1);
	(void)xft_tailor_bench(&t, benches, 5);
	xft_destroy_arena(xft_get_bench_arena());
	xft_tailor_destroy(&t);
	xft_exit(0);
}
