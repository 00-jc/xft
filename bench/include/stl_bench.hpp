/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_BENCH_HPP
# define STL_BENCH_HPP

# include <cstdint>

extern "C" {

# include "stl_bench_std.h"

/* the xft headers are C only: what the std:: side calls, with plain types */
uint64_t	xft_tailor_getcount(const void *ptr);
void		xft_tailor_add_processed_bytes(void *ptr, const uint64_t bytes);
uint64_t	xft_tailor_get_random_num(void *ptr);
uint64_t	*xft_get_bench_swiss_keys(void);
uint64_t	*xft_get_bench_swiss_large_keys(void);
t_stl_str	*xft_get_bench_str_keys(void);
t_stl_str	*xft_get_bench_str_large_keys(void);

}

#endif
