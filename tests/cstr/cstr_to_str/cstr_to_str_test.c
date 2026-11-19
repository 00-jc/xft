/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstr_to_str_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/cstr/cstr_to_str/cstr_to_str_test.h"

void	test_cstr_to_str(t_allocator a)
{
	t_str	s;

	xft_pin_invariant(xft_cstr_to_str(a, &s, "hello").ok);
	xft_pin_invariant(s.buf.size == 5);
	xft_pin_invariant(xft_memcmp(s.buf.mem, "hello", 6) == 0);
	xft_str_destroy(a, &s);
	xft_pin_invariant(!xft_cstr_to_str(a, &s, "").ok);
}

void	test_cstr(t_test *t)
{
	t_gpa		gpa;
	t_allocator	a;

	xft_pin_invariant(xft_new_gpa(&gpa).ok);
	a = xft_gpa_allocator(&gpa);
	xft_test_print(t, "Testing xft_cstr_to_str...\n");
	test_cstr_to_str(a);
	xft_gpa_destroy(&gpa);
	xft_test_print(t, "  xft_cstr_to_str: OK\n");
}
