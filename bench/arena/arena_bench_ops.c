/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_bench_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "alloc_bench.h"

t_arena	*ft_get_bench_arena(void)
{
	static t_arena				arena = {0};
	static t_arena_checkpoint	cp = {0};

	if (arena.current == nullptr)
	{
		arena = ft_new_arena_alloc();
		cp = ft_arena_checkpoint(&arena);
	}
	ft_arena_rewind(&arena, cp);
	return (&arena);
}

void	ft_arena_bench_8(void *ptr)
{
	t_arena	*arena;
	size_t	n;
	size_t	bytes;
	void	*p;

	arena = ft_get_bench_arena();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		p = ft_arena_alloc(arena, 8, 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += 8;
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}

void	ft_arena_bench_64(void *ptr)
{
	t_arena	*arena;
	size_t	n;
	size_t	bytes;
	void	*p;

	arena = ft_get_bench_arena();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		p = ft_arena_alloc(arena, 64, 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += 64;
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}

void	ft_arena_bench_512(void *ptr)
{
	t_arena	*arena;
	size_t	n;
	size_t	bytes;
	void	*p;

	arena = ft_get_bench_arena();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		p = ft_arena_alloc(arena, 512, 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += 512;
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}

void	ft_arena_bench_varied(void *ptr)
{
	static const size_t	sizes[4] = {8, 64, 256, 512};
	t_arena				*arena;
	size_t				n;
	size_t				bytes;
	void				*p;

	arena = ft_get_bench_arena();
	n = ft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		p = ft_arena_alloc(arena, sizes[n & 3], 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += sizes[n & 3];
	}
	ft_tailor_add_processed_bytes(ptr, bytes);
}
