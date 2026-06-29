/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   murmur_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/03 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_murmur_deterministic(void);
void	test_murmur_diff_input(void);
void	test_murmur_seed(void);
void	test_murmur_lengths(void);

void	test_murmur_deterministic(void)
{
	t_u128a	h1;
	t_u128a	h2;

	h1 = ft_murmur3((t_u8 *)"hello", 5);
	h2 = ft_murmur3((t_u8 *)"hello", 5);
	ft_pin_invariant(h1 == h2);
	h1 = ft_murmur3((t_u8 *)"world", 5);
	h2 = ft_murmur3((t_u8 *)"world", 5);
	ft_pin_invariant(h1 == h2);
}

void	test_murmur_diff_input(void)
{
	t_u128a	h1;
	t_u128a	h2;

	h1 = ft_murmur3((t_u8 *)"hello", 5);
	h2 = ft_murmur3((t_u8 *)"hellp", 5);
	ft_pin_invariant(h1 != h2);
	h1 = ft_murmur3((t_u8 *)"ab", 2);
	h2 = ft_murmur3((t_u8 *)"ba", 2);
	ft_pin_invariant(h1 != h2);
}

void	test_murmur_seed(void)
{
	t_u128a	h1;
	t_u128a	h2;

	h1 = ft_murmur3_with_seed((t_u8 *)"test", 0, 4);
	h2 = ft_murmur3_with_seed((t_u8 *)"test", 1, 4);
	ft_pin_invariant(h1 != h2);
	h1 = ft_murmur3_with_seed((t_u8 *)"test", 42, 4);
	h2 = ft_murmur3_with_seed((t_u8 *)"test", 42, 4);
	ft_pin_invariant(h1 == h2);
}

void	test_murmur_lengths(void)
{
	char	buf[512];
	t_u128a	prev;
	t_u128a	cur;
	int		i;

	memset(buf, 'A', 512);
	prev = ft_murmur3((t_u8 *)buf, 1);
	i = 2;
	while (i <= 512)
	{
		cur = ft_murmur3((t_u8 *)buf, i);
		ft_pin_invariant(cur != prev);
		prev = cur;
		i += (i < 32) + 1;
	}
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing ft_murmur3...\n");
	test_murmur_deterministic();
	test_murmur_diff_input();
	test_murmur_seed();
	test_murmur_lengths();
	ft_printf("  ft_murmur3: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
