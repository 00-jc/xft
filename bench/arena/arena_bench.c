/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 22:40:12 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"
#include "rt.h"

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	static t_tailor_bench	benches[] = {
	{ft_arena_bench_8, (t_blk8r)"arena_alloc_8"},
	{ft_arena_bench_64, (t_blk8r)"arena_alloc_64"},
	{ft_arena_bench_512, (t_blk8r)"arena_alloc_512"},
	{ft_arena_bench_varied, (t_blk8r)"arena_alloc_varied"},
	{ft_arena_bench_random, (t_blk8r)"arena_alloc_random"},
	};
	t_tailor				t;

	(void)argc;
	(void)argv;
	(void)envp;
	ft_bind_process_to_cpu(0);
	if (!ft_tailor_new(&t, 2, 2000))
		return (1);
	(void)ft_tailor_bench(&t, benches, 5);
	ft_destroy_arena(ft_get_bench_arena());
	ft_tailor_destroy(&t);
	return (0);
}
