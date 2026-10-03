/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_vec_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/08/26 20:36:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(2, 3), __always_inline__, hot, __used__))
inline t_result	xft_vec_push_back(t_allocator allocator,
		t_vec *restrict const vec,
		const t_u8 *restrict const data, t_size type_size)
{
	if (vec->buf.mem == nullptr || allocator.allocator == nullptr)
		__builtin_unreachable();
	{
		if (__builtin_expect(vec->size + type_size > vec->buf.size
				&& !xft_vec_reserve(allocator, vec,
					xft_tern(vec->buf.size, vec->buf.size << 1, 4)), 0))
			return (KO);
		xft_memcpy(vec->buf.mem + vec->size, data, type_size);
		vec->size += type_size;
		return (OK);
	}
}
