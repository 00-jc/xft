/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/03 18:51:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_memcmp_basic(void);
void	test_memcmp_binary(void);
void	test_memcmp_long(void);
void	test_memcmp_misaligned(void);

void	test_memcmp_basic(void)
{
	char	a[6];
	char	b[6];
	char	c[6];
	char	d[6];

	memcpy(a, "hello", 6);
	memcpy(b, "hello", 6);
	memcpy(c, "hellp", 6);
	memcpy(d, "hellm", 6);
	ft_pin_invariant(ft_memcmp(a, b, 5) == memcmp(a, b, 5));
	ft_pin_invariant((ft_memcmp(a, c, 5) < 0) == (memcmp(a, c, 5) < 0));
	ft_pin_invariant((ft_memcmp(a, d, 5) > 0) == (memcmp(a, d, 5) > 0));
	ft_pin_invariant(ft_memcmp(a, b, 0) == memcmp(a, b, 0));
	ft_pin_invariant(ft_memcmp(a, c, 4) == memcmp(a, c, 4));
}

void	test_memcmp_binary(void)
{
	unsigned char	a[5];
	unsigned char	b[5];
	unsigned char	c[5];
	unsigned char	d[5];

	a[0] = 0x00;
	a[1] = 0xFF;
	a[2] = 0x80;
	a[3] = 0x01;
	a[4] = 0x7F;
	memcpy(b, a, 5);
	memcpy(c, a, 5);
	memcpy(d, a, 5);
	c[2] = 0x81;
	d[1] = 0xFE;
	ft_pin_invariant(ft_memcmp(a, b, 5) == 0);
	ft_pin_invariant((ft_memcmp(a, c, 5) < 0) == (memcmp(a, c, 5) < 0));
	ft_pin_invariant((ft_memcmp(a, d, 5) > 0) == (memcmp(a, d, 5) > 0));
}

void	test_memcmp_long(void)
{
	char	a[256];
	char	b[256];
	char	c[256];
	int		i;

	i = 0;
	while (i < 256)
	{
		a[i] = (char)(i % 128);
		b[i] = a[i];
		c[i] = a[i];
		i++;
	}
	c[150] = 'X';
	ft_pin_invariant(ft_memcmp(a, b, 256) == 0);
	ft_pin_invariant((ft_memcmp(a, c, 256) != 0) == (memcmp(a, c, 256) != 0));
}

void	test_memcmp_misaligned(void)
{
	char	buf[128];
	char	ref[128];

	memset(buf, 'A', 128);
	memset(ref, 'A', 128);
	ft_pin_invariant(ft_memcmp(buf + 1, ref + 1, 50)
		== memcmp(buf + 1, ref + 1, 50));
	ft_pin_invariant(ft_memcmp(buf + 3, ref + 7, 30)
		== memcmp(buf + 3, ref + 7, 30));
	buf[10] = 'B';
	ref[10] = 'C';
	ft_pin_invariant((ft_memcmp(buf + 1, ref + 1, 20) > 0)
		== (memcmp(buf + 1, ref + 1, 20) > 0));
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing ft_memcmp...\n");
	test_memcmp_basic();
	test_memcmp_binary();
	test_memcmp_long();
	test_memcmp_misaligned();
	ft_printf("  ft_memcmp: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
