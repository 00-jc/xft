/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 07:17:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_map_insert_lookup(void);
void	test_map_delete(void);
void	test_map_overwrite(void);
void	test_map_many(void);

void	test_map_insert_lookup(void)
{
	t_map	m;
	int		val;
	int		*got;

	m = ft_map_new();
	val = 42;
	ft_pin_invariant(ft_map_insert(&m, (t_u8 *)"key1", 4, (t_u8 *)&val));
	got = ft_map_lookup(&m, (t_u8 *)"key1", 4);
	ft_pin_invariant(got != nullptr);
	ft_pin_invariant(*(int *)got == 42);
	ft_pin_invariant(ft_map_lookup(&m, (t_u8 *)"nope", 4) == nullptr);
	ft_map_destroy(&m);
}

void	test_map_delete(void)
{
	t_map	m;
	int		val;

	m = ft_map_new();
	val = 10;
	ft_map_insert(&m, (t_u8 *)"del", 3, (t_u8 *)&val);
	ft_pin_invariant(ft_map_lookup(&m, (t_u8 *)"del", 3) != nullptr);
	ft_map_delete(&m, (t_u8 *)"del", 3);
	ft_pin_invariant(ft_map_lookup(&m, (t_u8 *)"del", 3) == nullptr);
	ft_map_destroy(&m);
}

void	test_map_overwrite(void)
{
	t_map	m;
	int		v1;
	int		v2;
	int		*got;

	m = ft_map_new();
	v1 = 100;
	v2 = 200;
	ft_map_insert(&m, (t_u8 *)"ow", 2, (t_u8 *)&v1);
	ft_map_insert(&m, (t_u8 *)"ow", 2, (t_u8 *)&v2);
	got = ft_map_lookup(&m, (t_u8 *)"ow", 2);
	ft_pin_invariant(got != nullptr);
	ft_pin_invariant(*(int *)got == 200);
	ft_map_destroy(&m);
}

void	test_map_many(void)
{
	t_map	m;
	int		vals[200];
	int		i;
	int		*got;
	char	*k[200];

	m = ft_map_new();
	i = 0;
	while (i < 200)
	{
		vals[i] = i * 7;
		k[i] = ft_itoa(i);
		ft_map_insert(&m, (t_u8 *)k[i], ft_strlen(k[i]), (t_u8 *)&vals[i]);
		i++;
	}
	got = ft_map_lookup(&m, (t_u8 *)"0", 1);
	got = ft_map_lookup(&m, (t_u8 *)"199", 3);
	ft_pin_invariant(got && *got == 199 * 7);
	ft_map_destroy(&m);
	i = 0;
	while (i < 200)
		free(k[i++]);
}

int	main(void)
{
	ft_printf("Testing t_map (swissmap)...\n");
	test_map_insert_lookup();
	test_map_delete();
	test_map_overwrite();
	test_map_many();
	ft_printf("  t_map: OK\n");
	return (0);
}
