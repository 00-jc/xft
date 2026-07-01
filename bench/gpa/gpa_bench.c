/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bench.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:39:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"
#include "rt.h"

__attribute__((__always_inline__))
inline int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	static t_tailor_bench	benches[] = {
	{ft_gpa_bench_8, (t_blk8r)"gpa_alloc_free_8"},
	{ft_gpa_bench_64, (t_blk8r)"gpa_alloc_free_64"},
	{ft_gpa_bench_512, (t_blk8r)"gpa_alloc_free_512"},
	{ft_gpa_bench_8k, (t_blk8r)"gpa_alloc_free_8k"},
	{ft_gpa_bench_varied, (t_blk8r)"gpa_alloc_free_varied"},
	{ft_gpa_bench_random, (t_blk8r)"gpa_alloc_free_random"},
	{ft_gpa_bulk_bench_64, (t_blk8r)"gpa_bulk_64"},
	{ft_gpa_bulk_bench_512, (t_blk8r)"gpa_bulk_512"},
	{ft_gpa_bulk_bench_mixed, (t_blk8r)"gpa_bulk_mixed"},
	};
	t_tailor				t;

	(void)argc;
	(void)argv;
	(void)envp;
	ft_bind_process_to_cpu(0);
	if (!ft_tailor_new(&t, 2, 2000))
		return (1);
	return ((void)ft_tailor_bench(&t, benches, 9),
		ft_gpa_destroy(ft_get_bench_gpa()), ft_tailor_destroy(&t), 0);
}
