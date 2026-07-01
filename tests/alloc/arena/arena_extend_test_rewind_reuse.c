/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_extend_test_rewind_reuse.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_extend_test.h"

void	test_extend_rewind_reuse(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	t_hugepage			*second;
	void				*ptrs[2];
	t_size				big;

	a = ft_new_arena_alloc();
	big = a.current->total - a.current->used - 128;
	ft_arena_alloc(&a, big, 16);
	cp = ft_arena_checkpoint(&a);
	ptrs[0] = ft_arena_alloc(&a, 4096, 16);
	second = a.current;
	ft_pin_invariant_msg(second != cp.location,
		ft_fatptr((t_u8 *)"new page", sizeof("new page") - 1));
	ft_arena_rewind(&a, cp);
	ft_pin_invariant_msg(a.current == cp.location,
		ft_fatptr((t_u8 *)"rewound", sizeof("rewound") - 1));
	ptrs[1] = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(a.current == second,
		ft_fatptr((t_u8 *)"reused page", sizeof("reused page") - 1));
	ft_pin_invariant_msg(ptrs[1] == ptrs[0],
		ft_fatptr((t_u8 *)"same addr", sizeof("same addr") - 1));
	ft_destroy_arena(&a);
}
