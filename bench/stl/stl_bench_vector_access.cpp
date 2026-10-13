/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_vector_access.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "stl_bench.hpp"

/* at() for the bounds check xft_vec_get does */
void	xft_std_vector_bench_read(void *ptr)
{
	std::vector<uint64_t>	vec;
	uint64_t				n;
	uint64_t				val;
	const uint64_t			*r;

	vec.reserve(STL_BENCH_READ_FILL / sizeof(uint64_t));
	n = xft_tailor_getcount(ptr);
	val = 0;
	while (val < STL_BENCH_READ_FILL)
		vec.push_back(val++);
	while (n-- > 0)
	{
		r = &vec.at(xft_tailor_get_random_num(ptr) % STL_BENCH_READ_FILL);
		__asm__("" : : "r"(r) : "memory");
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(uint64_t));
}

void	xft_std_vector_bench_remove_front(void *ptr)
{
	std::vector<uint64_t>	vec;
	uint64_t				n;
	uint64_t				val;

	vec.reserve(STL_BENCH_RMF_LEN / sizeof(uint64_t));
	n = xft_tailor_getcount(ptr);
	val = 0;
	while (val < STL_BENCH_RMF_LEN)
		vec.push_back(val++);
	while (n-- > 0)
	{
		vec.push_back(val++);
		vec.erase(vec.begin());
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * STL_BENCH_RMF_LEN * sizeof(uint64_t));
}
