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

#include <xft/tailor.h>
#include "bench.h"
#include "stl_bench.h"

static_assert((t_size)STL_BENCH_FILL == (t_size)SWISS_BENCH_FILL);
static_assert((t_size)STL_BENCH_KEYS == (t_size)SWISS_BENCH_KEYS);
static_assert((t_size)STL_BENCH_LARGE_FILL == (t_size)SWISS_BENCH_LARGE_FILL);
static_assert((t_size)STL_BENCH_READ_FILL == (t_size)VEC_BENCH_READ_FILL);
static_assert((t_size)STL_BENCH_RMF_LEN == (t_size)VEC_BENCH_RMF_LEN);
static_assert(sizeof(t_stl_str) == sizeof(t_buffer));
static_assert(STL_STR_MAX == STL_STR_MIN + STL_STR_SPAN - 1);

void	xft_stl_bench_vector(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_std_vector_bench_push_back, "std_vec_push_back", "vec_push_back"},
	{xft_std_vector_bench_push_back_reserved, "std_vec_push_back_reserved",
		"vec_push_back_reserved"},
	{xft_std_vector_bench_push_pop, "std_vec_push_pop", "vec_push_pop"},
	{xft_std_vector_bench_read, "std_vec_read", "vec_read"},
	{xft_std_vector_bench_extend, "std_vec_extend", "vec_extend"},
	{xft_std_vector_bench_remove_front, "std_vec_remove_front",
		"vec_remove_front"},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}

/*
** 12..40 byte string keys and values: every map hashes the bytes
** (xxh3 vs std::hash<std::string_view> vs absl::Hash<std::string_view>)
*/

static void	xft_stl_bench_map_strings_insert(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_swiss_str_bench_insert_grow, "xft_map_strings_insert_grow",
		"map_strings_insert_grow"},
	{xft_std_umap_str_bench_insert_grow, "std_map_strings_insert_grow",
		"map_strings_insert_grow"},
	{xft_absl_flat_str_bench_insert_grow, "absl_map_strings_insert_grow",
		"map_strings_insert_grow"},
	{xft_swiss_str_bench_insert_reserved, "xft_map_strings_insert_reserved",
		"map_strings_insert_reserved"},
	{xft_std_umap_str_bench_insert_reserved, "std_map_strings_insert_reserved",
		"map_strings_insert_reserved"},
	{xft_absl_flat_str_bench_insert_reserved,
		"absl_map_strings_insert_reserved", "map_strings_insert_reserved"},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}

void	xft_stl_bench_map_strings(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_swiss_str_bench_lookup_hit, "xft_map_strings_lookup_hit",
		"map_strings_lookup_hit"},
	{xft_std_umap_str_bench_lookup_hit, "std_map_strings_lookup_hit",
		"map_strings_lookup_hit"},
	{xft_absl_flat_str_bench_lookup_hit, "absl_map_strings_lookup_hit",
		"map_strings_lookup_hit"},
	{xft_swiss_str_bench_lookup_miss, "xft_map_strings_lookup_miss",
		"map_strings_lookup_miss"},
	{xft_std_umap_str_bench_lookup_miss, "std_map_strings_lookup_miss",
		"map_strings_lookup_miss"},
	{xft_absl_flat_str_bench_lookup_miss, "absl_map_strings_lookup_miss",
		"map_strings_lookup_miss"},
	{xft_swiss_str_bench_delete_insert, "xft_map_strings_delete_insert",
		"map_strings_delete_insert"},
	{xft_std_umap_str_bench_delete_insert, "std_map_strings_delete_insert",
		"map_strings_delete_insert"},
	{xft_absl_flat_str_bench_delete_insert, "absl_map_strings_delete_insert",
		"map_strings_delete_insert"},
	};

	(void)xft_get_bench_str_keys();
	xft_stl_bench_map_strings_insert(t);
	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}

void	xft_stl_bench_map_strings_1m(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_swiss_str_bench_large_lookup_hit, "xft_map_strings_1m_lookup_hit",
		"map_strings_1m_lookup_hit"},
	{xft_std_umap_str_bench_large_lookup_hit, "std_map_strings_1m_lookup_hit",
		"map_strings_1m_lookup_hit"},
	{xft_absl_flat_str_bench_large_lookup_hit, "absl_map_strings_1m_lookup_hit",
		"map_strings_1m_lookup_hit"},
	{xft_swiss_str_bench_large_lookup_miss, "xft_map_strings_1m_lookup_miss",
		"map_strings_1m_lookup_miss"},
	{xft_std_umap_str_bench_large_lookup_miss, "std_map_strings_1m_lookup_miss",
		"map_strings_1m_lookup_miss"},
	{xft_absl_flat_str_bench_large_lookup_miss,
		"absl_map_strings_1m_lookup_miss", "map_strings_1m_lookup_miss"},
	{xft_swiss_str_bench_large_delete_insert,
		"xft_map_strings_1m_delete_insert", "map_strings_1m_delete_insert"},
	{xft_std_umap_str_bench_large_delete_insert,
		"std_map_strings_1m_delete_insert", "map_strings_1m_delete_insert"},
	{xft_absl_flat_str_bench_large_delete_insert,
		"absl_map_strings_1m_delete_insert", "map_strings_1m_delete_insert"},
	};

	(void)xft_get_bench_str_large_keys();
	(void)xft_tailor_bench_exclusive(t, benches,
		sizeof(benches) / sizeof(*benches));
}
