/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:01:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/28 23:12:01 by username         ###   ########.fr       */
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

	i = ft_fuzz_get_rand_u(fz) % FUZZ_KEY_SLOTS;
	val = (int)ft_fuzz_get_rand_u(fz);
	key = ft_fatptr(keys[i], 2);
	ft_printf("trying map slot %lu size %lu alignment to word %lu\n", i, 2UL,
		(t_uptr)(keys + i) & -(t_uptr)(keys + i));
	ft_pin_invariant(ft_map_insert(a, m, key, (t_u8 *)&val));
	x = ft_map_lookup(m, key);
	ft_pin_invariant(x != nullptr);
	ft_pin_invariant(*x == val);
	ft_map_delete(m, key);
	ft_pin_invariant(ft_map_lookup(m, key) == nullptr);
}

int	ft_main(t_size argc, t_u8 **argv, t_u8 **envp)
{
	t_fuzzer	fz;
	t_allocator	a;
	t_map		m;
	t_u8		keys[FUZZ_KEY_SLOTS][2];
	t_size		i;

	(void)argc;
	(void)argv;
	(void)envp;
	fz = ft_fuzzer_new(ft_new_arena_alloc());
	ft_pin_invariant(fz.arena.current != nullptr);
	ft_pin_invariant(ft_fuzzer_add_rand(&fz));
	a = ft_new_page_alloc();
	m = ft_map_new(a);
	init_keys(keys);
	i = 0;
	while (i++ < fz.buf_n * 2)
		fuzz_map_case(&fz, a, &m, keys);
	ft_map_destroy(a, &m);
	ft_fuzzer_destroy(&fz);
	return (0);
}
