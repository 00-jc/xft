/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   swissmap_bench_state.c                             :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/tailor.h>
#include "swissmap_bench.h"

t_gpa	*xft_get_bench_swiss_gpa(void)
{
	static t_gpa	gpa = {0};

	if (gpa.slab == nullptr)
		gpa = xft_new_gpa();
	return (&gpa);
}

t_u64a	*xft_get_bench_swiss_keys(void)
{
	static t_u64a	keys[SWISS_BENCH_KEYS] = {0};
	static t_result	ready = KO;
	t_xoshiro		rng;
	t_size			i;

	if (ready)
		return (keys);
	xft_xoshiro_init(rng);
	i = 0;
	while (i < SWISS_BENCH_KEYS)
		keys[i++] = xft_xoshiro256ss(rng);
	ready = OK;
	return (keys);
}

t_buffer	xft_swiss_bench_key(t_size i)
{
	return (xft_fatptr((t_u8 *)&xft_get_bench_swiss_keys()[i],
		sizeof(t_u64)));
}

t_swissmap	*xft_get_bench_swiss_filled(void)
{
	static t_swissmap	map = {0};
	t_allocator			a;
	t_size				i;

	if (map.soa.ptr != nullptr)
		return (&map);
	a = xft_gpa_allocator(xft_get_bench_swiss_gpa());
	map = xft_new_swissmap_with(a, SWISS_BENCH_FILL * 2);
	xft_pin_invariant(map.soa.ptr != nullptr);
	i = 0;
	while (i < SWISS_BENCH_FILL)
	{
		xft_pin_invariant(xft_swissmap_insert(a, &map,
				xft_swiss_bench_key(i), (t_u8 *)xft_get_bench_swiss_keys()));
		++i;
	}
	return (&map);
}
