/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test_reuse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/gpa/gpa_bulk_test.h"

void	test_bulk_reuse(void)
{
	t_buffer	bufs[BULK_N];
	t_gpa		gpa;
	t_buffer	b;
	int			i;

	gpa = xft_new_gpa();
	xft_pin_invariant_msg(gpa.slab != nullptr,
		xft_fatptr((t_u8 *)"gpa init reuse", sizeof("gpa init reuse") - 1));
	i = -1;
	while (++i < BULK_N)
		bufs[i] = xft_gpa_alloc(&gpa, 128, 8);
	i = BULK_N;
	while (--i >= 0)
		xft_gpa_free(&gpa, bufs[i]);
	i = -1;
	while (++i < BULK_N)
	{
		b = xft_gpa_alloc(&gpa, 128, 8);
		xft_pin_invariant_msg(b.mem != nullptr,
			xft_fatptr((t_u8 *)"reuse alloc", sizeof("reuse alloc") - 1));
		xft_pin_invariant_msg(b.size >= 128,
			xft_fatptr((t_u8 *)"reuse size", sizeof("reuse size") - 1));
		xft_gpa_free(&gpa, b);
	}
	xft_gpa_destroy(&gpa);
}
