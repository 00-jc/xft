/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_extend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:32:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 21:27:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(1), __always_inline__))
inline int	ft_vec_reserve(t_vec *restrict const vec,
		size_t type_size, size_t n)
{
	t_buffer	new_buf;
	size_t		new_cap;

	new_cap = n + vec->capacity;
	new_buf = ft_palloc_resize(vec->buf, new_cap * type_size);
	if (__builtin_expect(new_buf.mem != nullptr, 1))
	{
		vec->buf = new_buf;
		vec->capacity = new_buf.size / type_size;
		return (1);
	}
	return (0);
}

__attribute__((__nonnull__(1, 2)))
int	ft_vec_extend(t_vec *restrict const vec,
		const t_u8 *restrict const data, size_t type_size, size_t n)
{
	t_u8	should_extend;

	if (vec->buf.mem == nullptr)
		__builtin_unreachable();
	{
		should_extend = vec->capacity < vec->size + n;
		if (__builtin_expect(should_extend
				&& !ft_vec_reserve(vec, type_size, n), 0))
			return (0);
		ft_memcpy((t_u8 *)vec->buf.mem + (vec->size * type_size),
			data, n * type_size);
		vec->size += n;
	}
	return (1);
}
