/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_test_uniq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:13 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/alloc/arena/arena_test.h"

__attribute__((__nonnull__(1, 2)))
void	test_arena_uniq(t_arena *a, void *buf)
{
	void	*prev;
	void	*p;
	int		i;

	prev = buf;
	i = -1;
	while (++i < 5000)
	{
		p = ft_arena_alloc(a, 64, 8);
		ft_pin_invariant_msg(p != nullptr && p != prev,
			ft_fatptr((t_u8 *)"uniq", sizeof("uniq") - 1));
		prev = p;
	}
}
