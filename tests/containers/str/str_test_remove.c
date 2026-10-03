/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str_remove(t_allocator a)
{
	t_str		s;
	const t_u8	*src;

	src = (const t_u8 *)"abc";
	s = xft_new_str(a, 1);
	xft_pin_invariant(xft_str_extend(a, &s, src, 3));
	xft_pin_invariant(s.size == 3);
	xft_pin_invariant(xft_str_remove(&s, 1));
	xft_pin_invariant(s.size == 2);
	xft_pin_invariant(s.mem[0] == 'a');
	xft_pin_invariant(s.mem[1] == 'c');
	xft_pin_invariant(s.mem[2] == 0);
	xft_pin_invariant(!xft_str_remove(&s, 5));
	xft_pin_invariant(xft_str_remove(&s, 0));
	xft_pin_invariant(s.size == 1);
	xft_pin_invariant(s.mem[0] == 'c');
	xft_pin_invariant(s.mem[1] == 0);
	xft_pin_invariant(xft_str_remove(&s, 0));
	xft_pin_invariant(s.size == 0);
	xft_pin_invariant(s.mem[0] == 0);
	xft_str_destroy(a, &s);
}
