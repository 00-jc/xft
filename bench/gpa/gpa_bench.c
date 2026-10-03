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
inline void	xft_main(const t_any *__restrict__ const sp)
{
	static t_tailor_bench	benches[] = {
	{xft_gpa_bench_8, (t_blk8r)"gpa_alloc_free_8"},
	{xft_gpa_bench_64, (t_blk8r)"gpa_alloc_free_64"},
	{xft_gpa_bench_512, (t_blk8r)"gpa_alloc_free_512"},
	{xft_gpa_bench_8k, (t_blk8r)"gpa_alloc_free_8k"},
	{xft_gpa_bench_varied, (t_blk8r)"gpa_alloc_free_varied"},
	{xft_gpa_bench_random, (t_blk8r)"gpa_alloc_free_random"},
	{xft_gpa_bulk_bench_64, (t_blk8r)"gpa_bulk_64"},
	{xft_gpa_bulk_bench_512, (t_blk8r)"gpa_bulk_512"},
	{xft_gpa_bulk_bench_mixed, (t_blk8r)"gpa_bulk_mixed"},
	};
	t_tailor				t;

	(void)sp;
	xft_bind_process_to_cpu(0);
	if (!xft_new_tailor(&t, 2, 2000))
		xft_exit(1);
	(void)xft_tailor_bench(&t, benches, 9);
	xft_gpa_destroy(xft_get_bench_gpa());
	xft_tailor_destroy(&t);
	xft_exit(0);
}
