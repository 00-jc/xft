/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_extend_test_rewind_grow.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_extend_test.h"

void	test_extend_rewind_grow(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	t_hugepage			*pages[2];
	void				*p;
	t_size				big;

	a = ft_new_arena_alloc();
	pages[0] = a.current;
	big = pages[0]->total - pages[0]->used - 128;
	ft_arena_alloc(&a, big, 16);
	cp = ft_arena_checkpoint(&a);
	p = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(p != nullptr,
		ft_fatptr((t_u8 *)"first grow", sizeof("first grow") - 1));
	pages[1] = a.current;
	ft_arena_rewind(&a, cp);
	ft_pin_invariant_msg(a.current == pages[0],
		ft_fatptr((t_u8 *)"rewound", sizeof("rewound") - 1));
	p = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(p != nullptr,
		ft_fatptr((t_u8 *)"realloc", sizeof("realloc") - 1));
	ft_pin_invariant_msg(a.current == pages[1],
		ft_fatptr((t_u8 *)"reuse", sizeof("reuse") - 1));
	ft_destroy_arena(&a);
}
