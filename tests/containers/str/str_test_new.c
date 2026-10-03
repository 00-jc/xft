/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str_new(t_allocator a)
{
	t_str	s;

	s = xft_new_str(a, 1);
	xft_pin_invariant(s.mem != nullptr);
	xft_pin_invariant(s.size == 0);
	xft_pin_invariant(s.mem[0] == 0);
	xft_str_destroy(a, &s);
	xft_pin_invariant(s.mem == nullptr);
	xft_pin_invariant(s.size == 0);
	s = xft_new_str(a, 5);
	xft_pin_invariant(s.mem != nullptr);
	xft_pin_invariant(s.size == 0);
	xft_pin_invariant(s.mem[5] == 0);
	xft_str_destroy(a, &s);
}
