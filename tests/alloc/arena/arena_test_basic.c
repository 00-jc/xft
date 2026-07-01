/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test_basic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_test.h"

void	test_arena_basic(void)
{
	t_arena	a;
	t_u8	*buf;
	int		i;

	a = ft_new_arena_alloc();
	ft_pin_invariant_msg(a.current != nullptr,
		ft_fatptr((t_u8 *)"init", sizeof("init") - 1));
	buf = ft_arena_alloc(&a, 4096, 16);
	ft_pin_invariant_msg(buf != nullptr,
		ft_fatptr((t_u8 *)"alloc", sizeof("alloc") - 1));
	i = -1;
	while (++i < 4096)
		buf[i] = (t_u8)(i * 31 + 7);
	i = -1;
	while (++i < 4096)
		ft_pin_invariant_msg(buf[i] == (t_u8)(i * 31 + 7),
			ft_fatptr((t_u8 *)"rw", sizeof("rw") - 1));
	test_arena_uniq(&a, buf);
	ft_destroy_arena(&a);
}
