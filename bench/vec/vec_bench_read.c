/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:46:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:11:35 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "vec_bench.h"

#define READ_FILL	1024

__attribute__((__nonnull__(1)))
void	xft_vec_bench_read(t_any ptr)
{
	t_allocator	a;
	t_vec		vec;
	t_size		n;
	t_u64		val;

	a = xft_gpa_allocator(xft_get_bench_vec_gpa());
	vec = xft_vec(a, READ_FILL, sizeof(t_u64));
	n = xft_tailor_getcount(ptr);
	val = 0;
	while (val < READ_FILL)
	{
		xft_vec_push_back(a, &vec, (t_u8 *)&val, sizeof(val));
		val++;
	}
	while (n-- > 0)
	{
		val = xft_tailor_get_random_num(ptr) % READ_FILL;
		xft_pin_invariant(xft_vec_get(&vec, val, sizeof(t_u64)) != nullptr);
	}
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(t_u64));
	xft_vec_destroy(a, &vec);
}
