/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_map_insert_lookup(t_allocator a);
void	test_map_delete(t_allocator a);
void	test_map_overwrite(t_allocator a);
void	test_map_many(t_allocator a);

void	test_map_insert_lookup(t_allocator a)
{
	t_map	m;
	int		val;
	int		*got;

	m = ft_map_new(a);
	val = 42;
	ft_pin_invariant(ft_map_insert(a, &m,
			ft_fatptr((t_u8 *)"key1", 4), (t_u8 *)&val));
	got = ft_map_lookup(&m, ft_fatptr((t_u8 *)"key1", 4));
	ft_pin_invariant(got != nullptr);
	ft_pin_invariant(*(int *)got == 42);
	ft_pin_invariant(ft_map_lookup(&m,
			ft_fatptr((t_u8 *)"nope", 4)) == nullptr);
	ft_map_destroy(a, &m);
}

void	test_map_delete(t_allocator a)
{
	t_map	m;
	int		val;

	m = ft_map_new(a);
	val = 10;
	ft_map_insert(a, &m, ft_fatptr((t_u8 *)"del", 3), (t_u8 *)&val);
	ft_pin_invariant(ft_map_lookup(&m, ft_fatptr((t_u8 *)"del", 3)) != nullptr);
	ft_map_delete(&m, ft_fatptr((t_u8 *)"del", 3));
	ft_pin_invariant(ft_map_lookup(&m, ft_fatptr((t_u8 *)"del", 3)) == nullptr);
	ft_map_destroy(a, &m);
}

void	test_map_overwrite(t_allocator a)
{
	t_map	m;
	int		v1;
	int		v2;
	int		*got;

	m = ft_map_new(a);
	v1 = 100;
	v2 = 200;
	ft_map_insert(a, &m, ft_fatptr((t_u8 *)"ow", 2), (t_u8 *)&v1);
	ft_map_insert(a, &m, ft_fatptr((t_u8 *)"ow", 2), (t_u8 *)&v2);
	got = ft_map_lookup(&m, ft_fatptr((t_u8 *)"ow", 2));
	ft_pin_invariant(got != nullptr);
	ft_pin_invariant(*(int *)got == 200);
	ft_map_destroy(a, &m);
}

void	test_map_many(t_allocator a)
{
	t_map		m;
	t_xoshiro	rng;
	int			vals[200];
	t_u64a		keys[200];
	int			i;

	ft_xoshiro_init(rng);
	m = ft_map_new(a);
	i = 0;
	while (i < 200)
	{
		vals[i] = i * 7;
		keys[i] = ft_xoshiro256ss(rng);
		ft_map_insert(a, &m,
			ft_fatptr((t_u8 *)&keys[i], sizeof(t_u64a)), (t_u8 *)&vals[i]);
		i++;
	}
	ft_pin_invariant(*(int *)ft_map_lookup(&m,
			ft_fatptr((t_u8 *)&keys[i - 1], sizeof(t_u64a))) == 199 * 7);
	ft_map_destroy(a, &m);
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	t_gpa		gpa;
	t_allocator	a;

	gpa = ft_gpa();
	a = ft_gpa_allocator(&gpa);
	ft_printf("Testing t_map (swissmap)...\n");
	test_map_insert_lookup(a);
	test_map_delete(a);
	test_map_overwrite(a);
	test_map_many(a);
	ft_gpa_destroy(&gpa);
	ft_printf("  t_map: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
