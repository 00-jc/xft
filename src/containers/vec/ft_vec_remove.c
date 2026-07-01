/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(1)))
t_result	ft_vec_remove(t_vec *restrict const v, size_t i, size_t type_size)
{
	t_u8		*elem;
	const t_u8	*last;

	if (v->buf.mem == nullptr)
		__builtin_unreachable();
	elem = ft_vec_get_mut(v, i, type_size);
	last = ft_vec_peek_last(v, type_size);
	if (elem == nullptr || last == nullptr)
		return (KO);
	ft_memmove(elem, elem + type_size, (t_uptr)last - (t_uptr)elem);
	--v->size;
	return (OK);
}

__attribute__((__nonnull__(1)))
t_result	ft_vec_removef(t_vec *restrict const v, size_t i, size_t type_size,
		void (*f)(void *))
{
	t_u8		*elem;
	const t_u8	*last;

	if (v->buf.mem == nullptr)
		__builtin_unreachable();
	elem = ft_vec_get_mut(v, i, type_size);
	last = ft_vec_peek_last(v, type_size);
	if (elem == nullptr || last == nullptr)
		return (KO);
	f(elem);
	ft_memmove(elem, elem + type_size, (t_uptr)last - (t_uptr)elem);
	--v->size;
	return (OK);
}
