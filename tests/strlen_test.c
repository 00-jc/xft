/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 03:25:05 by jaicastr          #+#    #+#             */
/*   Updated: 2026/02/19 20:29:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/test.h"

void	test_strlen_basic(void);
void	test_strlen_misaligned(void);
void	test_strlen_long(void);

void	test_strlen_basic(void)
{
	char	h[6];
	char	w[6];
	char	z[1];

	memcpy(h, "hello", 6);
	memcpy(w, "world", 6);
	memcpy(z, "\0\0", 1);
	ft_pin_invariant(ft_strlen(h) == strlen(h));
	ft_pin_invariant(ft_strlen(w) == strlen(w));
	ft_pin_invariant(ft_strlen(z) == strlen(z));
	ft_pin_invariant(ft_strlen("") == strlen(""));
	ft_pin_invariant(ft_strlen("a") == strlen("a"));
}

void	test_strlen_misaligned(void)
{
	char	h[10];
	char	w[10];

	memcpy(h, "hello", 6);
	memcpy(w, "world", 6);
	ft_pin_invariant(ft_strlen(h + 1) == strlen(h + 1));
	ft_pin_invariant(ft_strlen(w + 2) == strlen(w + 2));
	ft_pin_invariant(ft_strlen(h + 3) == strlen(h + 3));
	ft_pin_invariant(ft_strlen(w + 1) == strlen(w + 1));
}

void	test_strlen_long(void)
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
	ft_pin_invariant(ft_strlen(buf) == strlen(buf));
	ft_pin_invariant(ft_strlen(buf + 1) == strlen(buf + 1));
	ft_pin_invariant(ft_strlen(buf + 10) == strlen(buf + 10));
	ft_pin_invariant(ft_strlen(buf + 63) == strlen(buf + 63));
}

int	ft_main(t_u64a argc, t_u8 **argv, t_u8 **envp)
{
	ft_printf("Testing ft_strlen...\n");
	test_strlen_basic();
	test_strlen_misaligned();
	test_strlen_long();
	ft_printf("  ft_strlen: OK\n");
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
