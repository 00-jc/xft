/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test_push_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/vec/vec_test.h"

void	test_vec_push_get(t_allocator a)
{
	t_vec		v;
	int			val;
	const int	*got;

	v = ft_vec(a, 4, sizeof(int));
	ft_pin_invariant(v.buf.mem != nullptr);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 0);
	val = 42;
	ft_pin_invariant(ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int)));
	val = 99;
	ft_pin_invariant(ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int)));
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 2);
	got = ft_vec_get(&v, 0, sizeof(int));
	ft_pin_invariant(got && *got == 42);
	got = ft_vec_get(&v, 1, sizeof(int));
	ft_pin_invariant(got && *got == 99);
	ft_pin_invariant(ft_vec_get(&v, 2, sizeof(int)) == nullptr);
	ft_vec_destroy(a, &v);
}
