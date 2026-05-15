/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:32:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:14:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(1, 2), __always_inline__, hot))
inline int	ft_vec_push_back(t_vec *restrict const vec,
		const t_u8 *restrict const data, size_t type_size)
{
	if (vec->data == nullptr)
		__builtin_unreachable();
	{
		if (__builtin_expect(vec->size == vec->capacity
				&& !ft_vec_reserve(vec, type_size,
					ft_tern(vec->capacity, vec->capacity << 1, 4)), 0))
			return (0);
		ft_memcpy((t_u8 *)vec->data + (vec->size * type_size), data, type_size);
		++vec->size;
		return (1);
	}
}
