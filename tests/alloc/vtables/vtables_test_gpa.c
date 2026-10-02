/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtables_test_gpa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/vtables/vtables_test.h"

void	test_gpa_vtable(void)
{
	t_gpa		gpa;
	t_allocator	alloc;
	t_buffer	buf;

	gpa = xft_gpa();
	xft_pin_invariant_msg(gpa.slab != nullptr,
		xft_fatptr((t_u8 *)"gpa: init", sizeof("gpa: init") - 1));
	alloc = xft_gpa_allocator(&gpa);
	buf = alloc.vtable.allocate(alloc.allocator, 64, 8);
	xft_pin_invariant_msg(buf.mem != nullptr,
		xft_fatptr((t_u8 *)"gpa: alloc non-null",
			sizeof("gpa: alloc non-null") - 1));
	xft_pin_invariant_msg(buf.size >= 64,
		xft_fatptr((t_u8 *)"gpa: alloc size", sizeof("gpa: alloc size") - 1));
	buf.mem[0] = 0xCA;
	buf.mem[63] = 0xFE;
	xft_pin_invariant_msg(buf.mem[0] == 0xCA,
		xft_fatptr((t_u8 *)"gpa: rw lo", sizeof("gpa: rw lo") - 1));
	xft_pin_invariant_msg(buf.mem[63] == 0xFE,
		xft_fatptr((t_u8 *)"gpa: rw hi", sizeof("gpa: rw hi") - 1));
	test_gpa_vtable_realloc(&alloc, buf);
}
