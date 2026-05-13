/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 19:01:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuzz.h"

static void	init_keys(t_u8 keys[FUZZ_KEY_SLOTS][2])
{
	size_t	i;

	i = 0;
	while (i < FUZZ_KEY_SLOTS)
	{
		keys[i][0] = (t_u8)i;
		keys[i][1] = (t_u8)(i ^ 0x5A);
		++i;
	}
}

static void	fuzz_map_case(t_fuzzer *fz, t_map *m, t_u8 keys[FUZZ_KEY_SLOTS][2])
{
	size_t	i;
	int		val;
	int		*x;

	i = ft_fuzz_get_rand_u(fz) % FUZZ_KEY_SLOTS;
	val = (int)ft_fuzz_get_rand_u(fz);
	ft_printf("trying map slot %lu size %lu alignment to word %lu\n", i, 2UL,
		(t_uptr)(keys + i) & -(t_uptr)(keys + i));
	ft_pin_invariant(ft_map_insert(m, keys[i], 2, (t_u8 *)&val));
	x = ft_map_lookup(m, keys[i], 2);
	ft_pin_invariant(x != nullptr);
	ft_pin_invariant(*x == val);
	ft_map_delete(m, keys[i], 2);
	ft_pin_invariant(ft_map_lookup(m, keys[i], 2) == nullptr);
}

int	main(void)
{
	t_fuzzer	fz;
	t_map		m;
	t_u8		keys[FUZZ_KEY_SLOTS][2];
	size_t		i;
	size_t		n;

	fz = ft_fuzzer_new(ft_new_arena_alloc());
	ft_pin_invariant(fz.arena.current != nullptr);
	ft_pin_invariant(ft_fuzzer_add_rand(&fz));
	m = ft_map_new();
	init_keys(keys);
	n = fz.buf_n * 2;
	i = 0;
	while (i++ < n)
		fuzz_map_case(&fz, &m, keys);
	ft_map_destroy(&m);
	ft_fuzzer_destroy(&fz);
	return (0);
}
