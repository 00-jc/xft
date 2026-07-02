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
void	ft_vec_bench_extend(void *ptr)
{
	static const t_u64	chunk[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	t_allocator			a;
	t_vec				*vec;
	t_size				n;

	vec = ft_get_bench_vec();
	a = ft_gpa_allocator(ft_get_bench_vec_gpa());
	n = ft_tailor_getcount(ptr);
	while (n-- > 0)
		ft_vec_extend(a, vec,
			(t_buffer){.mem = (t_u8 *)chunk, .size = sizeof(chunk)});
	ft_tailor_add_processed_bytes(ptr,
		ft_tailor_getcount(ptr) * sizeof(chunk));
}
