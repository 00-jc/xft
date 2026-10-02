/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench_extend.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:46:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:10:40 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "vec_bench.h"

__attribute__((__nonnull__(1)))
void	xft_vec_bench_extend(t_any ptr)
{
	static const t_u64	chunk[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	t_allocator			a;
	t_vec				vec;
	t_size				n;

	a = xft_gpa_allocator(xft_get_bench_vec_gpa());
	vec = xft_vec(a, 64, sizeof(t_u64));
	n = xft_tailor_getcount(ptr);
	while (n-- > 0)
		xft_vec_extend(a, &vec,
			(t_buffer){.mem = (t_u8 *)chunk, .size = sizeof(chunk)});
	xft_tailor_add_processed_bytes(ptr,
		xft_tailor_getcount(ptr) * sizeof(chunk));
	xft_vec_destroy(a, &vec);
}
