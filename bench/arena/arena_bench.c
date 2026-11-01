/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_bench.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 23:40:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "alloc_bench.h"
#include <xft/rt.h>
#include "bench.h"

void	xft_bench_arena(t_tailor *t)
{
	static t_tailor_bench	benches[] = {
	{xft_arena_bench_8, "arena_alloc_8", nullptr},
	{xft_arena_bench_64, "arena_alloc_64", nullptr},
	{xft_arena_bench_512, "arena_alloc_512", nullptr},
	{xft_arena_bench_varied, "arena_alloc_varied", nullptr},
	{xft_arena_bench_random, "arena_alloc_random", nullptr},
	};

	(void)xft_tailor_bench(t, benches, sizeof(benches) / sizeof(*benches));
}
