/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 01:27:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_memcpy_basic(void);
void	test_memcpy_misaligned(void);
void	test_memmove_backward(void);
void	test_memcpy_large(void);

void	test_memcpy_basic(void)
{
	char	src[20];
	char	a[20];
	char	b[20];

	memcpy(src, "hello world12345", 17);
	ft_memcpy(a, src, 17);
	memcpy(b, src, 17);
	ft_pin_invariant(memcmp(a, b, 17) == 0);
	ft_memcpy(a, src, 0);
	ft_pin_invariant(memcmp(a, b, 17) == 0);
	memcpy(src, "hello world1", 13);
	ft_memcpy(a, src, 13);
	memcpy(b, src, 13);
	ft_pin_invariant(memcmp(a, b, 13) == 0);
	ft_memcpy(a, src, 0);
	ft_pin_invariant(memcmp(a, b, 13) == 0);
	memcpy(src, "hello world1", 3);
	ft_memcpy(a, src, 3);
	memcpy(b, src, 3);
	ft_pin_invariant(memcmp(a, b, 3) == 0);
	ft_memcpy(a, src, 0);
	ft_pin_invariant(memcmp(a, b, 3) == 0);
}

void	test_memcpy_misaligned(void)
{
	char	src[256];
	char	a[256];
	char	b[256];
	int		i;

	i = 0;
	while (i < 255)
	{
		src[i] = 'A' + (i % 26);
		i++;
	}
	src[255] = '\0';
	ft_memcpy(a + 1, src + 3, 100);
	memcpy(b + 1, src + 3, 100);
	ft_pin_invariant(memcmp(a + 1, b + 1, 100) == 0);
}

void	test_memmove_backward(void)
{
	char	a[512];
	char	b[512];
	int		i;

	i = 0;
	while (i < 512)
	{
		a[i] = (char)(i & 0xFF);
		b[i] = (char)(i & 0xFF);
		i++;
	}
	ft_memmove(a + 10, a + 3, 200);
	memmove(b + 10, b + 3, 200);
	ft_pin_invariant(memcmp(a, b, 512) == 0);
}

void	test_memcpy_large(void)
{
	char	a[4096];
	char	b[4096];
	int		i;

	i = 0;
	while (i < 4096)
	{
		a[i] = 'A' + (i % 26);
		i++;
	}
	ft_memcpy(b, a, 4096);
	ft_pin_invariant(memcmp(a, b, 4096) == 0);
	ft_memcpy(b + 1, a + 3, 2000);
	ft_pin_invariant(memcmp(b + 1, a + 3, 2000) == 0);
}

int	main(void)
{
	ft_printf("Testing ft_memcpy/ft_memmove...\n");
	test_memcpy_basic();
	test_memcpy_misaligned();
	test_memmove_backward();
	test_memcpy_large();
	ft_printf("  ft_memcpy/ft_memmove: OK\n");
	return (0);
}
