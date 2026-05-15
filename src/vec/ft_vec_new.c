/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:23:57 by jaicastr          #+#    #+#             */
/*   Updated: 2026/01/19 04:38:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec	ft_vec_new(size_t size, size_t type_size)
{
	t_buffer	buf;
	size_t		mul;

	mul = size * type_size;
	if (mul == 0 || (mul / size != type_size))
		return ((t_vec){0});
	buf = ft_palloc(mul);
	return ((t_vec)
		{
			.size = 0,
			.capacity = buf.size / type_size,
			.buf = buf,
		});
}
