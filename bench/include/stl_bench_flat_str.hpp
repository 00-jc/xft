/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_flat_str.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_BENCH_FLAT_STR_HPP
# define STL_BENCH_FLAT_STR_HPP

# include <absl/container/flat_hash_map.h>
# include "stl_bench.hpp"

/* borrowed keys and values like t_std_umap_str; absl::Hash reads the bytes */
typedef absl::flat_hash_map<std::string_view, std::string_view>
	t_absl_flat_str;

t_absl_flat_str	&xft_get_bench_absl_flat_str_filled(void);
t_absl_flat_str	&xft_get_bench_absl_flat_str_large_filled(void);
void			xft_absl_flat_str_lookup(void *ptr,
					const t_absl_flat_str &map, const t_stl_str *keys,
					uint64_t range);
void			xft_absl_flat_str_delete_insert(void *ptr,
					t_absl_flat_str &map, const t_stl_str *keys,
					uint64_t range);

#endif
