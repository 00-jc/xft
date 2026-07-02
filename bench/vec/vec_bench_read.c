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
void	ft_vec_bench_read(void *ptr)
{
	t_allocator	a;
	t_vec		*vec;
	t_size		n;
	t_u64		val;

	vec = ft_get_bench_vec();
	a = ft_gpa_allocator(ft_get_bench_vec_gpa());
	n = ft_tailor_getcount(ptr);
	val = 0;
	while (val < READ_FILL)
	{
		ft_vec_push_back(a, vec, (t_u8 *)&val, sizeof(val));
		val++;
	}
	while (n-- > 0)
	{
		val = ft_tailor_get_random_num(ptr) % READ_FILL;
		ft_pin_invariant(ft_vec_get(vec, val, sizeof(t_u64)) != nullptr);
	}
	ft_tailor_add_processed_bytes(ptr,
		ft_tailor_getcount(ptr) * sizeof(t_u64));
}
