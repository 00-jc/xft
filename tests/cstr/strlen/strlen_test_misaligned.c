/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_test_misaligned.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:08 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/cstr/strlen/strlen_test.h"

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
