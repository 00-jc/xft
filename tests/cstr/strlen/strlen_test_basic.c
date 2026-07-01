/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_test_basic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/cstr/strlen/strlen_test.h"

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
