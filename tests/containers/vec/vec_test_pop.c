/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/vec/vec_test.h"

void	test_vec_pop(t_allocator a)
{
	t_vec	v;
	int		val;
	int		out;

	v = ft_vec(a, 4, sizeof(int));
	val = 10;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	val = 20;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	val = 30;
	ft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	ft_pin_invariant(ft_vec_popmv(&v, &out, sizeof(int)));
	ft_pin_invariant(out == 30);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 2);
	ft_vec_pop(&v);
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 1);
	ft_vec_destroy(a, &v);
}
