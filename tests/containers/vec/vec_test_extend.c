/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_test_extend.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 21:35:09 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 13:33:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/containers/vec/vec_test.h"

void	test_vec_extend(t_allocator a)
{
	t_vec		v;
	int			data[5];
	const int	*got;
	int			i;

	v = ft_vec(a, 2, sizeof(int));
	i = 0;
	while (i < 5)
	{
		data[i] = i * 10;
		i++;
	}
	ft_pin_invariant(ft_vec_extend(a, &v,
			(t_buffer){.mem = (t_u8 *)data, .size = sizeof(data)}));
	ft_pin_invariant(ft_vec_len(&v, sizeof(int)) == 5);
	got = ft_vec_get(&v, 3, sizeof(int));
	ft_pin_invariant(got && *got == 30);
	got = ft_vec_get(&v, 4, sizeof(int));
	ft_pin_invariant(got && *got == 40);
	ft_vec_destroy(a, &v);
}
