/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:19:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/13 06:14:05 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(1)))
int	ft_vec_remove(t_vec *restrict const v, size_t i, size_t type_size)
{
	t_u8		*elem;
	const t_u8	*last;

	if (!v->data)
		return (0);
	elem = ft_vec_get_mut(v, i, type_size);
	last = ft_vec_peek_last(v, type_size);
	if (elem == nullptr || last == nullptr)
		return (0);
	ft_memmove(elem, elem + type_size, (t_uptr)last - (t_uptr)elem);
	--v->size;
	return (1);
}

__attribute__((__nonnull__(1)))
int	ft_vec_removef(t_vec *restrict const v, size_t i, size_t type_size,
		void (*f)(void *))
{
	t_u8		*elem;
	const t_u8	*last;

	if (!v->data)
		return (0);
	elem = ft_vec_get_mut(v, i, type_size);
	last = ft_vec_peek_last(v, type_size);
	if (elem == nullptr || last == nullptr)
		return (0);
	f(elem);
	ft_memmove(elem, elem + type_size, (t_uptr)last - (t_uptr)elem);
	--v->size;
	return (1);
}
