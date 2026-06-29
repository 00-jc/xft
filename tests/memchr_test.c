/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 03:39:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/03/03 18:50:57 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_memchr_basic(void);
void	test_memchr_edge(void);
void	test_memchr_misaligned(void);
void	test_memchr_long(void);

void	test_memchr_basic(void)
{
	char	h[6];
	char	w[6];
	char	z[1];

	memcpy(h, "hello", 6);
	memcpy(w, "world", 6);
	z[0] = '\0';
	ft_pin_invariant(ft_memchr(h, 'h', 5) == memchr(h, 'h', 5));
	ft_pin_invariant(ft_memchr(h, 'e', 5) == memchr(h, 'e', 5));
	ft_pin_invariant(ft_memchr(h, 'o', 5) == memchr(h, 'o', 5));
	ft_pin_invariant(ft_memchr(w, 'w', 5) == memchr(w, 'w', 5));
	ft_pin_invariant(ft_memchr(h, 'x', 5) == memchr(h, 'x', 5));
	ft_pin_invariant(ft_memchr(z, 'a', 0) == memchr(z, 'a', 0));
	ft_pin_invariant(ft_memchr(h, '\0', 6) == memchr(h, '\0', 6));
}

void	test_memchr_edge(void)
{
	char	h[6];
	char	w[6];

	memcpy(h, "hello", 6);
	memcpy(w, "world", 6);
	ft_pin_invariant(ft_memchr(h, 'h', 0) == memchr(h, 'h', 0));
	ft_pin_invariant(ft_memchr(h, 'e', 1) == memchr(h, 'e', 1));
	ft_pin_invariant(ft_memchr(h, 'h', 1) == memchr(h, 'h', 1));
	ft_pin_invariant(ft_memchr(w, 'w', 1) == memchr(w, 'w', 1));
	ft_pin_invariant(ft_memchr(h, 'l', 5) == memchr(h, 'l', 5));
	ft_pin_invariant(ft_memchr(h + 3, 'l', 2) == memchr(h + 3, 'l', 2));
	ft_pin_invariant(ft_memchr(h, '\0', 5) == memchr(h, '\0', 5));
	ft_pin_invariant(ft_memchr(h, 'x', 4) == memchr(h, 'x', 4));
	ft_pin_invariant(ft_memchr(w, 'd', 6) == memchr(w, 'd', 6));
}

void	test_memchr_misaligned(void)
{
	char	h[10];
	char	w[10];

	memcpy(h, "hello", 6);
	memcpy(w, "world", 6);
	ft_pin_invariant(ft_memchr(h + 1, 'e', 4) == memchr(h + 1, 'e', 4));
	ft_pin_invariant(ft_memchr(h + 1, 'l', 4) == memchr(h + 1, 'l', 4));
	ft_pin_invariant(ft_memchr(h + 3, 'l', 2) == memchr(h + 3, 'l', 2));
	ft_pin_invariant(ft_memchr(h + 4, 'o', 1) == memchr(h + 4, 'o', 1));
	ft_pin_invariant(ft_memchr(w + 2, 'r', 3) == memchr(w + 2, 'r', 3));
	ft_pin_invariant(ft_memchr(w + 3, 'l', 2) == memchr(w + 3, 'l', 2));
	ft_pin_invariant(ft_memchr(w + 1, 'o', 4) == memchr(w + 1, 'o', 4));
	ft_pin_invariant(ft_memchr(h + 5, 'h', 1) == memchr(h + 5, 'h', 1));
}

void	test_memchr_long(void)
{
	char	buf[256];
	int		i;

	i = 0;
	while (i < 255)
	{
		buf[i] = 'A' + (i % 26);
		i++;
	}
	buf[255] = '\0';
	ft_pin_invariant(ft_memchr(buf, 'A', 256) == memchr(buf, 'A', 256));
	ft_pin_invariant(ft_memchr(buf, 'Z', 256) == memchr(buf, 'Z', 256));
	ft_pin_invariant(ft_memchr(buf + 10, 'A', 100)
		== memchr(buf + 10, 'A', 100));
	ft_pin_invariant(ft_memchr(buf + 63, 'B', 50) == memchr(buf + 63, 'B', 50));
	ft_pin_invariant(ft_memchr(buf, '\0', 256) == memchr(buf, '\0', 256));
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing ft_memchr...\n");
	test_memchr_basic();
	test_memchr_edge();
	test_memchr_misaligned();
	test_memchr_long();
	ft_printf("  ft_memchr: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
