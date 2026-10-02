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

t_arena	*xft_get_bench_arena(void)
{
	static t_arena				arena = {0};
	static t_arena_checkpoint	cp = {0};

	if (arena.current == nullptr)
	{
		arena = xft_new_arena_alloc();
		cp = xft_arena_checkpoint(&arena);
	}
	xft_arena_rewind(&arena, cp);
	return (&arena);
}

void	xft_arena_bench_8(t_any ptr)
{
	t_arena	*arena;
	t_size	n;
	t_size	bytes;
	t_any	p;

	arena = xft_get_bench_arena();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		p = xft_arena_alloc(arena, 8, 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += 8;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_arena_bench_64(t_any ptr)
{
	t_arena	*arena;
	t_size	n;
	t_size	bytes;
	t_any	p;

	arena = xft_get_bench_arena();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		p = xft_arena_alloc(arena, 64, 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += 64;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_arena_bench_512(t_any ptr)
{
	t_arena	*arena;
	t_size	n;
	t_size	bytes;
	t_any	p;

	arena = xft_get_bench_arena();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		p = xft_arena_alloc(arena, 512, 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += 512;
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}

void	xft_arena_bench_varied(t_any ptr)
{
	static const t_size	sizes[4] = {8, 64, 256, 512};
	t_arena				*arena;
	t_size				n;
	t_size				bytes;
	t_any				p;

	arena = xft_get_bench_arena();
	n = xft_tailor_getcount(ptr);
	bytes = 0;
	while (n-- > 0)
	{
		p = xft_arena_alloc(arena, sizes[n & 3], 8);
		__asm__("": "+r,m"(p) ::"memory");
		bytes += sizes[n & 3];
	}
	xft_tailor_add_processed_bytes(ptr, bytes);
}
