/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test_edge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memchr/memchr_test.h"

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
