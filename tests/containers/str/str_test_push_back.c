/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_test_push_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/str/str_test.h"

void	test_str_push_back(t_allocator a)
{
	t_str	s;

	xft_pin_invariant(xft_new_str(a, &s, 1).ok);
	xft_pin_invariant(xft_str_push_back(a, &s, 'h').ok);
	xft_pin_invariant(xft_str_push_back(a, &s, 'i').ok);
	xft_pin_invariant(s.buf.size == 2);
	xft_pin_invariant(s.buf.mem[0] == 'h');
	xft_pin_invariant(s.buf.mem[1] == 'i');
	xft_pin_invariant(s.buf.mem[2] == 0);
	xft_str_destroy(a, &s);
}
