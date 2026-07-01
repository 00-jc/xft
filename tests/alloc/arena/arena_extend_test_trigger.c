/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_extend_test_trigger.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_extend_test.h"

void	test_extend_trigger(void)
{
	t_arena		a;
	t_hugepage	*first;
	void		*p;
	t_size		big;

	a = ft_new_arena_alloc();
	first = a.current;
	ft_pin_invariant_msg(first->next == nullptr,
		ft_fatptr((t_u8 *)"no next yet", sizeof("no next yet") - 1));
	big = first->total - first->used - 128;
	p = ft_arena_alloc(&a, big, 16);
	ft_pin_invariant_msg(p != nullptr,
		ft_fatptr((t_u8 *)"fill page", sizeof("fill page") - 1));
	ft_pin_invariant_msg(a.current == first,
		ft_fatptr((t_u8 *)"still first", sizeof("still first") - 1));
	p = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(p != nullptr,
		ft_fatptr((t_u8 *)"overflow alloc", sizeof("overflow alloc") - 1));
	ft_pin_invariant_msg(a.current != first,
		ft_fatptr((t_u8 *)"moved fwd", sizeof("moved fwd") - 1));
	ft_pin_invariant_msg(a.current->prev == first,
		ft_fatptr((t_u8 *)"prev link", sizeof("prev link") - 1));
	ft_pin_invariant_msg(first->next == a.current,
		ft_fatptr((t_u8 *)"next link", sizeof("next link") - 1));
	ft_destroy_arena(&a);
}
