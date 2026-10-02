/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr_test_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/mem/memchr/memchr_test.h"

void	test_memchr_basic(void)
{
	char	h[6];
	char	w[6];
	char	z[1];

	memcpy(h, "hello", 6);
	memcpy(w, "world", 6);
	z[0] = '\0';
	xft_pin_invariant(xft_memchr(h, 'h', 5) == memchr(h, 'h', 5));
	xft_pin_invariant(xft_memchr(h, 'e', 5) == memchr(h, 'e', 5));
	xft_pin_invariant(xft_memchr(h, 'o', 5) == memchr(h, 'o', 5));
	xft_pin_invariant(xft_memchr(w, 'w', 5) == memchr(w, 'w', 5));
	xft_pin_invariant(xft_memchr(h, 'x', 5) == memchr(h, 'x', 5));
	xft_pin_invariant(xft_memchr(z, 'a', 0) == memchr(z, 'a', 0));
	xft_pin_invariant(xft_memchr(h, '\0', 6) == memchr(h, '\0', 6));
}
