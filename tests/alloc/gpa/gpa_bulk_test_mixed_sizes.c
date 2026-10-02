/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test_mixed_sizes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/gpa/gpa_bulk_test.h"

void	test_bulk_mixed_sizes(void)
{
	t_buffer	bufs[BULK_N];
	t_gpa		gpa;
	int			i;

	gpa = xft_gpa();
	xft_pin_invariant_msg(gpa.slab != nullptr,
		xft_fatptr((t_u8 *)"gpa init mixed", sizeof("gpa init mixed") - 1));
	test_bulk_mixed_sizes_fill(&gpa, bufs);
	i = -1;
	while (++i < BULK_N)
		xft_pin_invariant_msg(*bufs[i].mem == (t_u8)(i & 0xff),
			xft_fatptr((t_u8 *)"mixed rw", sizeof("mixed rw") - 1));
	i = -1;
	while (++i < BULK_N)
		xft_gpa_free(&gpa, bufs[i]);
	xft_gpa_destroy(&gpa);
}
