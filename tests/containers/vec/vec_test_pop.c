/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 13:20:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/vec/vec_test.h"

void	test_vec_pop(t_allocator a)
{
	t_vec	v;
	int		val;
	int		out;

	v = xft_new_vec(a, 4, sizeof(int));
	val = 10;
	xft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	val = 20;
	xft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	val = 30;
	xft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	xft_pin_invariant(xft_vec_popmv(&v, &out, sizeof(int)));
	xft_pin_invariant(out == 30);
	xft_pin_invariant(xft_vec_len(&v, sizeof(int)) == 2);
	xft_vec_pop(&v, sizeof(int));
	xft_pin_invariant(xft_vec_len(&v, sizeof(int)) == 1);
	xft_vec_destroy(a, &v);
}
