/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test_misaligned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memchr/memchr_test.h"

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
