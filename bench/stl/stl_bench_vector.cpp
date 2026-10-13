/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_vector.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "stl_bench.hpp"

/* xft_new_vec(a, 64, sizeof(t_u64)) takes bytes: 8 elements */
#define STL_VEC_INITIAL	(64 / sizeof(uint64_t))

void	xft_std_vector_bench_push_back(void *ptr)
{
	std::vector<uint64_t>	vec;
	uint64_t				n;
	uint64_t				val;

	vec.reserve(STL_VEC_INITIAL);
	n = xft_tailor_getcount(ptr);
	val = 0;
	while (n-- > 0)
		vec.push_back(val++);
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(uint64_t));
}

void	xft_std_vector_bench_push_back_reserved(void *ptr)
{
	std::vector<uint64_t>	vec;
	uint64_t				n;
	uint64_t				val;

	n = xft_tailor_getcount(ptr);
	vec.reserve(n);
	val = 0;
	while (n-- > 0)
		vec.push_back(val++);
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(uint64_t));
}

void	xft_std_vector_bench_push_pop(void *ptr)
{
	std::vector<uint64_t>	vec;
	uint64_t				n;
	uint64_t				val;

	vec.reserve(STL_VEC_INITIAL);
	n = xft_tailor_getcount(ptr);
	val = 0;
	while (n-- > 0)
	{
		vec.push_back(val);
		val = vec.back();
		vec.pop_back();
		__asm__("": "+r,m"(val) ::"memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(uint64_t) * 2);
}

void	xft_std_vector_bench_extend(void *ptr)
{
	static const uint64_t	chunk[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	std::vector<uint64_t>	vec;
	uint64_t				n;

	vec.reserve(STL_VEC_INITIAL);
	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
		vec.insert(vec.end(), chunk, chunk + 8);
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(chunk));
}
