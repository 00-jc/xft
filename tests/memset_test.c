/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/16 04:11:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_memset_basic(void);
void	test_memset_large(void);
void	test_memset_misaligned(void);
void	test_bzero_large(void);

void	test_memset_basic(void)
{
	char	a[64];
	char	b[64];

	ft_memset(a, 'X', 64);
	memset(b, 'X', 64);
	ft_pin_invariant(memcmp(a, b, 64) == 0);
	ft_memset(a, 0, 64);
	memset(b, 0, 64);
	ft_pin_invariant(memcmp(a, b, 64) == 0);
	ft_memset(a, 0xFF, 32);
	memset(b, 0xFF, 32);
	ft_pin_invariant(memcmp(a, b, 64) == 0);
}

void	test_memset_large(void)
{
	char	a[4096];
	char	b[4096];
	int		i;

	i = 0;
	while (i < 256)
	{
		ft_memset(a, (t_u8)i, 4096);
		memset(b, i, 4096);
		ft_pin_invariant(memcmp(a, b, 4096) == 0);
		i += 85;
	}
}

void	test_memset_misaligned(void)
{
	char	a[4096];
	char	b[4096];
	int		off;

	off = 1;
	while (off < 64)
	{
		ft_memset(a + off, 'Z', 4096 - off);
		memset(b + off, 'Z', 4096 - off);
		ft_pin_invariant(memcmp(a + off, b + off, 4096 - off) == 0);
		off += 7;
	}
}

void	test_bzero_large(void)
{
	char	a[4096];
	char	b[4096];

	memset(a, 'A', 4096);
	memset(b, 'A', 4096);
	ft_bzero(a, 4096);
	memset(b, 0, 4096);
	ft_pin_invariant(memcmp(a, b, 4096) == 0);
	memset(a, 'B', 4096);
	ft_bzero(a + 13, 3000);
	ft_pin_invariant(a[12] == 'B');
	ft_pin_invariant(a[13] == 0);
	ft_pin_invariant(a[3012] == 0);
	ft_pin_invariant(a[3013] == 'B');
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing ft_memset/ft_bzero (SIMD)...\n");
	test_memset_basic();
	test_memset_large();
	test_memset_misaligned();
	test_bzero_large();
	ft_printf("  ft_memset/ft_bzero: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
