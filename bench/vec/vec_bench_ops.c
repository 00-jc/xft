/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bench_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:46:16 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:13:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_syscalls.h"
#include "tailor.h"
#include "vec_bench.h"

void	ft_vec_bench_push_back(void *ptr)
{
	t_allocator	a;
	t_vec		*vec;
	t_size		n;
	t_size		bytes;
	t_u64		val;

	vec = ft_get_bench_vec();
	a = ft_gpa_allocator(ft_get_bench_vec_gpa());
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	val = 0;
	while (n-- > 0)
	{
		ft_vec_push_back(a, vec, (t_u8 *)&val, sizeof(val));
		bytes += sizeof(val);
		val++;
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}

void	ft_vec_bench_push_back_reserved(void *ptr)
{
	t_allocator	a;
	t_vec		*vec;
	t_size		n;
	t_size		needed;
	t_u64		val;

	vec = ft_get_bench_vec();
	a = ft_gpa_allocator(ft_get_bench_vec_gpa());
	n = ft_tailor_getcount(ptr);
	ft_vec_clear(vec);
	needed = n * sizeof(t_u64);
	if (vec->buf.size < needed)
		ft_vec_reserve(a, vec, needed - vec->buf.size);
	val = 0;
	while (n-- > 0)
	{
		ft_vec_push_back(a, vec, (t_u8 *)&val, sizeof(val));
		val++;
	}
	ft_tailor_add_processed_bytes(ptr, ft_tailor_getcount(ptr) * sizeof(t_u64));
}

__attribute__((__nonnull__(1)))
void	ft_vec_bench_push_pop(void *ptr)
{
	t_allocator	a;
	t_vec		*vec;
	t_size		n;
	t_u64		val;

	vec = ft_get_bench_vec();
	a = ft_gpa_allocator(ft_get_bench_vec_gpa());
	n = ft_tailor_getcount(ptr);
	val = 0;
	while (n-- > 0)
	{
		ft_vec_push_back(a, vec, (t_u8 *)&val, sizeof(val));
		ft_vec_popmv(vec, &val, sizeof(t_u64));
		__asm__("": "+r,m"(val) ::"memory");
	}
	ft_tailor_add_processed_bytes(ptr,
		ft_tailor_getcount(ptr) * sizeof(t_u64) * 2);
}
