/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test_clear_reuse.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 21:35:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/vec/vec_test.h"

void	test_vec_clear_reuse(t_allocator a)
{
	t_vec		v;
	int			val;
	const int	*got;

	v = xft_vec(a, 8, sizeof(int));
	val = 100;
	xft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	val = 200;
	xft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	xft_pin_invariant(xft_vec_len(&v, sizeof(int)) == 2);
	xft_vec_clear(&v);
	xft_pin_invariant(xft_vec_len(&v, sizeof(int)) == 0);
	val = 300;
	xft_vec_push_back(a, &v, (t_u8 *)&val, sizeof(int));
	got = xft_vec_get(&v, 0, sizeof(int));
	xft_pin_invariant(got && *got == 300);
	xft_pin_invariant(xft_vec_len(&v, sizeof(int)) == 1);
	xft_vec_destroy(a, &v);
}
