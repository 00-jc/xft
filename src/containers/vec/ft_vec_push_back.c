/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/26 20:36:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(2, 3), __always_inline__, hot))
inline t_result	ft_vec_push_back(t_allocator allocator,
		t_vec *restrict const vec,
		const t_u8 *restrict const data, t_size type_size)
{
	if (vec->buf.mem == nullptr || allocator.allocator == nullptr)
		__builtin_unreachable();
	{
		if (__builtin_expect(vec->size + type_size > vec->buf.size
				&& !ft_vec_reserve(allocator, vec,
					ft_tern(vec->buf.size, vec->buf.size << 1, 4)), 0))
			return (KO);
		ft_memcpy(vec->buf.mem + vec->size, data, type_size);
		vec->size += type_size;
		return (OK);
	}
}
