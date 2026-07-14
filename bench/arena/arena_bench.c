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
inline void	ft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{ft_arena_bench_8, (t_blk8r)"arena_alloc_8"},
	{ft_arena_bench_64, (t_blk8r)"arena_alloc_64"},
	{ft_arena_bench_512, (t_blk8r)"arena_alloc_512"},
	{ft_arena_bench_varied, (t_blk8r)"arena_alloc_varied"},
	{ft_arena_bench_random, (t_blk8r)"arena_alloc_random"},
	};
	t_tailor				t;

	(void)sp;
	ft_bind_process_to_cpu(0);
	if (!ft_tailor_new(&t, 2, 2000))
		ft_exit(1);
	(void)ft_tailor_bench(&t, benches, 5);
	ft_destroy_arena(ft_get_bench_arena());
	ft_tailor_destroy(&t);
	ft_exit(0);
}
