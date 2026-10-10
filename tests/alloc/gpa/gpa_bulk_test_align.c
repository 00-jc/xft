/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test_align.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 22:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/10 22:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/gpa/gpa_bulk_test.h"

static void	check_aligned(t_buffer b, t_size align)
{
	xft_pin_invariant_msg(b.mem != nullptr,
		xft_fatptr((t_u8 *)"align alloc", sizeof("align alloc") - 1));
	xft_pin_invariant_msg(((t_uptr)b.mem & (align - 1)) == 0,
		xft_fatptr((t_u8 *)"align reuse", sizeof("align reuse") - 1));
}

static void	align_round(t_gpa *gpa, t_buffer *bufs, t_size size)
{
	int	i;

	i = -1;
	while (++i < BULK_N)
		bufs[i] = xft_gpa_alloc(gpa, size, 1);
	while (--i >= 0)
		xft_gpa_free(gpa, bufs[i]);
	while (++i < BULK_N)
	{
		bufs[i] = xft_gpa_alloc(gpa, size, size);
		check_aligned(bufs[i], size);
	}
	while (--i >= 0)
	{
		bufs[i] = xft_gpa_realloc(gpa, bufs[i], size, size << 1);
		check_aligned(bufs[i], size << 1);
		xft_gpa_free(gpa, bufs[i]);
	}
}

void	test_bulk_align(void)
{
	t_buffer	bufs[BULK_N];
	t_gpa		gpa;
	t_size		size;

	gpa = xft_new_gpa();
	xft_pin_invariant_msg(gpa.slab != nullptr,
		xft_fatptr((t_u8 *)"gpa init align", sizeof("gpa init align") - 1));
	size = 8;
	while (size <= 4096)
	{
		align_round(&gpa, bufs, size);
		size <<= 1;
	}
	xft_gpa_destroy(&gpa);
}
