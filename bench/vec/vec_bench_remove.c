/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:46:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:11:59 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "vec_bench.h"

#define RMF_LEN	256

__attribute__((__nonnull__(1)))
void	ft_vec_bench_remove_front(void *ptr)
{
	t_allocator	a;
	t_vec		*vec;
	t_size		n;
	t_u64		val;

	vec = ft_get_bench_vec();
	a = ft_gpa_allocator(ft_get_bench_vec_gpa());
	n = ft_tailor_getcount(ptr);
	val = 0;
	while (val < RMF_LEN)
	{
		ft_vec_push_back(a, vec, (t_u8 *)&val, sizeof(val));
		val++;
	}
	while (n-- > 0)
	{
		ft_vec_push_back(a, vec, (t_u8 *)&val, sizeof(val));
		ft_vec_remove(vec, 0, sizeof(t_u64));
		val++;
	}
	ft_tailor_add_processed_bytes(ptr,
		ft_tailor_getcount(ptr) * RMF_LEN * sizeof(t_u64));
}
