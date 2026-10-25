/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_BENCH_H
# define STL_BENCH_H

# include "tailor.h"
# include "vec_bench.h"
# include "swissmap_bench.h"
# include "stl_bench_str.h"
# include "stl_bench_std.h"

void	xft_stl_bench_vector(t_tailor *t);
void	xft_stl_bench_map(t_tailor *t);
void	xft_stl_bench_map_strings(t_tailor *t);
void	xft_stl_bench_map_strings_1m(t_tailor *t);

#endif
