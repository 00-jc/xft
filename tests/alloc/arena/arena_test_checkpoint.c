/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test_checkpoint.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_test.h"

void	test_arena_checkpoint(void)
{
	t_arena				a;
	t_arena_checkpoint	cp;
	void				*p1;
	void				*p2;
	void				*p3;

	a = ft_new_arena_alloc();
	p1 = ft_arena_alloc(&a, 64, 8);
	cp = ft_arena_checkpoint(&a);
	p2 = ft_arena_alloc(&a, 128, 8);
	ft_pin_invariant_msg(p2 != nullptr,
		ft_fatptr((t_u8 *)"after cp", sizeof("after cp") - 1));
	ft_arena_rewind(&a, cp);
	p3 = ft_arena_alloc(&a, 128, 8);
	ft_pin_invariant_msg(p3 == p2,
		ft_fatptr((t_u8 *)"rewind addr", sizeof("rewind addr") - 1));
	(void)p1;
	ft_arena_rewind_clean(&a, cp);
	p3 = ft_arena_alloc(&a, 64, 8);
	ft_pin_invariant_msg(p3 != nullptr,
		ft_fatptr((t_u8 *)"after clean", sizeof("after clean") - 1));
	ft_destroy_arena(&a);
}
