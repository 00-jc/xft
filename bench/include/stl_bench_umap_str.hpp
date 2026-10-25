/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_umap_str.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_BENCH_UMAP_STR_HPP
# define STL_BENCH_UMAP_STR_HPP

# include <string_view>
# include <unordered_map>
# include "stl_bench.hpp"

/* the swissmap does not own its keys or values, so neither does this one:
   std::string would bench the allocator on every insert instead */
typedef std::unordered_map<std::string_view, std::string_view>	t_std_umap_str;

t_std_umap_str	&xft_get_bench_std_umap_str_filled(void);
t_std_umap_str	&xft_get_bench_std_umap_str_large_filled(void);
void			xft_std_umap_str_lookup(void *ptr, const t_std_umap_str &map,
					const t_stl_str *keys, uint64_t range);
void			xft_std_umap_str_delete_insert(void *ptr, t_std_umap_str &map,
					const t_stl_str *keys, uint64_t range);

inline std::string_view	xft_stl_str_view(const t_stl_str &s)
{
	return (std::string_view(reinterpret_cast<const char *>(s.mem), s.size));
}

#endif
