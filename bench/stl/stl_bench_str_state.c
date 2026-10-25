/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_bench_str_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/25 12:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "stl_bench_str.h"

/* base64url, so each char is 6 bits of a draw: 10 chars per xoshiro call */
void	xft_bench_str_gen(t_stl_str *strs, t_u8 *pool, t_size n)
{
	static const char	set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789-_";
	t_xoshiro			rng;
	t_u64				r;
	t_size				j;

	xft_xoshiro_init(rng);
	while (n-- > 0)
	{
		r = xft_xoshiro256ss(rng);
		*strs = (t_stl_str){.size = STL_STR_MIN + r % STL_STR_SPAN,
			.mem = pool};
		j = 0;
		while (j < strs->size)
		{
			if (j % 10 == 0)
				r = xft_xoshiro256ss(rng);
			pool[j++] = (t_u8)set[r & 63];
			r >>= 6;
		}
		pool += (strs++)->size;
	}
}

t_stl_str	*xft_get_bench_str_keys(void)
{
	static t_stl_str	keys[STL_BENCH_KEYS] = {0};
	static t_u8			pool[STL_BENCH_KEYS * STL_STR_MAX] = {0};
	static t_result		ready = KO;

	if (ready)
		return (keys);
	xft_bench_str_gen(keys, pool, STL_BENCH_KEYS);
	ready = OK;
	return (keys);
}

t_stl_str	*xft_get_bench_str_large_keys(void)
{
	static t_stl_str	keys[STL_BENCH_LARGE_FILL * 2] = {0};
	static t_u8			pool[STL_BENCH_LARGE_FILL * 2 * STL_STR_MAX] = {0};
	static t_result		ready = KO;

	if (ready)
		return (keys);
	xft_bench_str_gen(keys, pool, STL_BENCH_LARGE_FILL * 2);
	ready = OK;
	return (keys);
}
