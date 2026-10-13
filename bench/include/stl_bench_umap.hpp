/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_umap.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_BENCH_UMAP_HPP
# define STL_BENCH_UMAP_HPP

# include <unordered_map>
# include "stl_bench.hpp"

/* the swissmap stores a t_u8 * per key; std::hash<uint64_t> is the default */
typedef std::unordered_map<uint64_t, uint8_t *>	t_std_umap;

t_std_umap	&xft_get_bench_std_umap_filled(void);
t_std_umap	&xft_get_bench_std_umap_large_filled(void);
void		xft_std_umap_lookup(void *ptr, const t_std_umap &map,
				const uint64_t *keys, uint64_t base, uint64_t range);
void		xft_std_umap_delete_insert(void *ptr, t_std_umap &map,
				uint64_t *keys, uint64_t range);

#endif
