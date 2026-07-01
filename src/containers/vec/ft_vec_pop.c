/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_pop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__always_inline__, __nonnull__(1)))
inline void	ft_vec_pop(t_vec *restrict const v)
{
	v->size -= v->size != 0;
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
		ft_vec_pop(v);
		return (OK);
	}
	return (KO);
}

__attribute__((__always_inline__, __nonnull__(1)))
inline t_result	ft_vec_popf(t_vec *restrict const v, size_t type_size,
	void (*f)(void *))
{
	t_u8	*last;

	if (v->buf.mem == nullptr)
		__builtin_unreachable();
	last = ft_vec_get_last(v, type_size);
	if (__builtin_expect(last != nullptr, 1))
	{
		f(last);
		ft_vec_pop(v);
		return (OK);
	}
	return (KO);
}
