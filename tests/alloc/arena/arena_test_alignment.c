/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test_alignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_test.h"

void	test_arena_alignment(void)
{
	t_arena	a;
	void	*p;
	t_size	aligns[7];
	t_size	i;

	aligns[0] = 1;
	aligns[1] = 2;
	aligns[2] = 4;
	aligns[3] = 8;
	aligns[4] = 16;
	aligns[5] = 32;
	aligns[6] = 64;
	a = ft_new_arena_alloc();
	i = -1;
	while (++i < 7)
	{
		p = ft_arena_alloc(&a, 17, aligns[i]);
		ft_pin_invariant_msg(p != nullptr,
			ft_fatptr((t_u8 *)"aligned alloc", sizeof("aligned alloc") - 1));
		ft_pin_invariant_msg(((t_uptr)p & (aligns[i] - 1)) == 0,
			ft_fatptr((t_u8 *)"align ok", sizeof("align ok") - 1));
	}
	ft_destroy_arena(&a);
}
