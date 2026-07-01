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

	gpa = ft_gpa();
	ft_pin_invariant_msg(gpa.slab != nullptr,
		ft_fatptr((t_u8 *)"gpa init reuse", sizeof("gpa init reuse") - 1));
	i = -1;
	while (++i < BULK_N)
		bufs[i] = ft_gpa_alloc(&gpa, 128, 8);
	i = BULK_N;
	while (--i >= 0)
		ft_gpa_free(&gpa, bufs[i]);
	i = -1;
	while (++i < BULK_N)
	{
		b = ft_gpa_alloc(&gpa, 128, 8);
		ft_pin_invariant_msg(b.mem != nullptr,
			ft_fatptr((t_u8 *)"reuse alloc", sizeof("reuse alloc") - 1));
		ft_pin_invariant_msg(b.size >= 128,
			ft_fatptr((t_u8 *)"reuse size", sizeof("reuse size") - 1));
		ft_gpa_free(&gpa, b);
	}
	ft_gpa_destroy(&gpa);
}
