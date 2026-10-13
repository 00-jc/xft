/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "stl_bench.h"

static_assert(STL_BENCH_FILL == SWISS_BENCH_FILL);
static_assert(STL_BENCH_KEYS == SWISS_BENCH_KEYS);
static_assert(STL_BENCH_LARGE_FILL == SWISS_BENCH_LARGE_FILL);
static_assert(STL_BENCH_READ_FILL == VEC_BENCH_READ_FILL);
static_assert(STL_BENCH_RMF_LEN == VEC_BENCH_RMF_LEN);

void	xft_stl_bench_vector(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_vec_bench_push_back, (t_blk8r)"xft_vec_push_back"},
	{xft_std_vector_bench_push_back, (t_blk8r)"std_vector_push_back"},
	{xft_vec_bench_push_back_reserved, (t_blk8r)"xft_vec_push_back_reserved"},
	{xft_std_vector_bench_push_back_reserved,
		(t_blk8r)"std_vector_push_back_reserved"},
	{xft_vec_bench_push_pop, (t_blk8r)"xft_vec_pop"},
	{xft_std_vector_bench_push_pop, (t_blk8r)"std_vector_pop"},
	{xft_vec_bench_read, (t_blk8r)"xft_vec_read"},
	{xft_std_vector_bench_read, (t_blk8r)"std_vector_read"},
	{xft_vec_bench_extend, (t_blk8r)"xft_vec_extend"},
	{xft_std_vector_bench_extend, (t_blk8r)"std_vector_extend"},
	{xft_vec_bench_remove_front, (t_blk8r)"xft_vec_remove_front"},
	{xft_std_vector_bench_remove_front, (t_blk8r)"std_vector_remove_front"},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}

void	xft_stl_bench_map(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_swiss_bench_insert_grow, (t_blk8r)"xft_swiss_insert_grow"},
	{xft_std_umap_bench_insert_grow, (t_blk8r)"std_umap_insert_grow"},
	{xft_swiss_bench_insert_reserved, (t_blk8r)"xft_swiss_insert_reserved"},
	{xft_std_umap_bench_insert_reserved, (t_blk8r)"std_umap_insert_reserved"},
	{xft_swiss_bench_lookup_hit, (t_blk8r)"xft_swiss_lookup_hit"},
	{xft_std_umap_bench_lookup_hit, (t_blk8r)"std_umap_lookup_hit"},
	{xft_swiss_bench_lookup_miss, (t_blk8r)"xft_swiss_lookup_miss"},
	{xft_std_umap_bench_lookup_miss, (t_blk8r)"std_umap_lookup_miss"},
	{xft_swiss_bench_delete_insert, (t_blk8r)"xft_swiss_delete_insert"},
	{xft_std_umap_bench_delete_insert, (t_blk8r)"std_umap_delete_insert"},
	{xft_swiss_bench_large_lookup_hit, (t_blk8r)"xft_swiss_1m_lookup_hit"},
	{xft_std_umap_bench_large_lookup_hit, (t_blk8r)"std_umap_1m_lookup_hit"},
	{xft_swiss_bench_large_lookup_miss, (t_blk8r)"xft_swiss_1m_lookup_miss"},
	{xft_std_umap_bench_large_lookup_miss, (t_blk8r)"std_umap_1m_lookup_miss"},
	{xft_swiss_bench_large_delete_insert,
		(t_blk8r)"xft_swiss_1m_delete_insert"},
	{xft_std_umap_bench_large_delete_insert,
		(t_blk8r)"std_umap_1m_delete_insert"},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
