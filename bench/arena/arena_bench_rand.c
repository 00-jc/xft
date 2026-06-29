/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_bench_rand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"

void	ft_arena_bench_random(void *ptr)
{
	t_arena		*arena;
	t_size		n;
	t_size		bytes;
	t_size		sz;
	void		*p;

	arena = ft_get_bench_arena();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		sz = 8ULL << (ft_tailor_get_random_num(ptr) % 14);
		p = ft_arena_alloc(arena, sz, 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += sz;
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}
