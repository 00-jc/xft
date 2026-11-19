/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_vec_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 02:11:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/vec.h>

__attribute__((__nonnull__(2, 3), __always_inline__, hot, __used__))
inline t_result	xft_vec_push_back(t_allocator allocator,
		t_vec *restrict const vec,
		const t_u8 *restrict const data, t_size type_size)
{
	t_result	ret;

	if (vec->buf.mem == nullptr || allocator.allocator == nullptr)
		__builtin_unreachable();
	{
		ret = (t_result){.ok = OK};
		if (__builtin_expect(vec->buf.size + type_size > vec->buf.capacity, 0))
			ret = xft_vec_reserve(allocator, vec,
					xft_tern_s(vec->buf.capacity, vec->buf.capacity << 1, 4));
		if (__builtin_expect(!ret.ok, 0))
			return (ret);
		__builtin_memcpy(vec->buf.mem + vec->buf.size, data, type_size);
		vec->buf.size += type_size;
		return ((t_result){.ok = OK});
	}
}
