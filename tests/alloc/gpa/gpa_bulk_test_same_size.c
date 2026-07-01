/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpa_bulk_test_same_size.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/gpa/gpa_bulk_test.h"

void	test_bulk_same_size(void)
{
	t_buffer	bufs[BULK_N];
	t_gpa		gpa;
	int			i;

	gpa = ft_gpa();
	ft_pin_invariant_msg(gpa.slab != nullptr,
		ft_fatptr((t_u8 *)"gpa init", sizeof("gpa init") - 1));
	test_bulk_same_size_fill(&gpa, bufs);
	i = -1;
	while (++i < BULK_N)
		ft_pin_invariant_msg(*(t_u64 *)bufs[i].mem == (t_u64)i,
			ft_fatptr((t_u8 *)"bulk rw", sizeof("bulk rw") - 1));
	i = BULK_N;
	while (--i >= 0)
		ft_gpa_free(&gpa, bufs[i]);
	ft_gpa_destroy(&gpa);
}
