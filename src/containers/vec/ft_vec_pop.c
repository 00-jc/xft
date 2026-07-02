/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:15:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline void	ft_vec_pop(t_vec *restrict const v, t_size type_size)
{
	v->size -= -(v->size != 0) & type_size;
}

__attribute__((__always_inline__, __nonnull__(1)))
inline t_result	ft_vec_popmv(t_vec *restrict const v, void *const dest,
	size_t type_size)
{
	t_u8	*last;

	if (v->buf.mem == nullptr)
		__builtin_unreachable();
	last = ft_vec_get_last(v, type_size);
	if (__builtin_expect(last != nullptr, 1))
	{
		ft_memcpy(dest, last, type_size);
		ft_vec_pop(v, type_size);
		return (OK);
	}
	return (KO);
}

__attribute__((__always_inline__, __nonnull__(2)))
inline t_result	ft_vec_pop_managed(t_allocator allocator,
	t_vec *restrict const v, size_t type_size)
{
	t_u8	*last;

	if (v->buf.mem == nullptr || allocator.allocator == nullptr
		|| allocator.interface.free == nullptr)
		__builtin_unreachable();
	last = ft_vec_get_last(v, type_size);
	if (__builtin_expect(last != nullptr, 1))
	{
		allocator.interface.free(allocator.allocator, *(t_buffer *)last);
		ft_vec_pop(v, type_size);
		return (OK);
	}
	return (KO);
}
