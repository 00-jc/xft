/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:15 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:50:52 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzz.h"

static void	init_keys(t_u8 keys[FUZZ_KEY_SLOTS][2])
{
	t_size	i;

	i = 0;
	while (i < FUZZ_KEY_SLOTS)
	{
		keys[i][0] = (t_u8)i;
		keys[i][1] = (t_u8)(i ^ 0x5A);
		++i;
	}
}

static void	fuzz_map_case(t_fuzzer *fz, t_allocator a,
		t_map *m, t_u8 keys[FUZZ_KEY_SLOTS][2])
{
	t_buffer	key;
	t_size		i;
	int			val;
	int			*x;

	i = xft_fuzz_get_rand_u(fz) % FUZZ_KEY_SLOTS;
	val = (int)xft_fuzz_get_rand_u(fz);
	key = xft_fatptr(keys[i], 2);
	xft_pin_invariant(xft_map_insert(a, m, key, (t_u8 *)&val));
	x = xft_map_lookup(m, key);
	xft_pin_invariant(x != nullptr);
	xft_pin_invariant(*x == val);
	xft_map_delete(m, key);
	xft_pin_invariant(xft_map_lookup(m, key) == nullptr);
}

void	xft_main(const t_any *__restrict__ const sp)
{
	t_fuzzer	fz;
	t_allocator	a;
	t_map		m;
	t_u8		keys[FUZZ_KEY_SLOTS][2];
	t_size		i;

	(void)sp;
	fz = xft_fuzzer_new(xft_new_arena_alloc());
	xft_pin_invariant(fz.arena.current != nullptr);
	xft_pin_invariant(xft_fuzzer_add_rand(&fz));
	a = xft_new_page_alloc();
	m = xft_map_new(a);
	init_keys(keys);
	i = 0;
	while (i++ < fz.buf_n * 2)
		fuzz_map_case(&fz, a, &m, keys);
	xft_map_destroy(a, &m);
	xft_fuzzer_destroy(&fz);
	xft_exit(0);
}
