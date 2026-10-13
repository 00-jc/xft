/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexmap_bench_large_state.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 21:30:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:30:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tailor.h"
#include "indexmap_bench.h"

t_u64a	*xft_get_bench_imap_large_keys(void)
{
	static t_u64a	keys[IMAP_BENCH_LARGE_FILL * 2] = {0};
	static t_result	ready = KO;
	t_xoshiro		rng;
	t_size			i;

	if (ready)
		return (keys);
	xft_xoshiro_init(rng);
	i = 0;
	while (i < IMAP_BENCH_LARGE_FILL * 2)
		keys[i++] = xft_xoshiro256ss(rng);
	ready = OK;
	return (keys);
}

t_buffer	xft_imap_bench_large_key(t_size i)
{
	return (xft_fatptr((t_u8 *)&xft_get_bench_imap_large_keys()[i],
		sizeof(t_u64)));
}

t_indexmap	*xft_get_bench_imap_large_filled(void)
{
	static t_indexmap	map = {0};
	t_allocator			a;
	t_size				i;

	if (map.soa.ptr != nullptr)
		return (&map);
	a = xft_gpa_allocator(xft_get_bench_imap_gpa());
	map = xft_new_indexmap_with(a, IMAP_BENCH_LARGE_FILL * 2);
	xft_pin_invariant(map.soa.ptr != nullptr);
	i = 0;
	while (i < IMAP_BENCH_LARGE_FILL)
	{
		xft_pin_invariant(xft_indexmap_insert(a, &map,
				xft_imap_bench_large_key(i),
				i));
		++i;
	}
	return (&map);
}
