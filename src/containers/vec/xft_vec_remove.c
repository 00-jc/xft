/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_vec_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 14:15:58 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/vec.h>

__attribute__((__nonnull__(1)))
t_result	xft_vec_remove(t_vec *restrict const v, t_size i, t_size type_size)
{
	t_u8		*elem;
	const t_u8	*last;

	if (v->buf.mem == nullptr)
		__builtin_unreachable();
	elem = xft_vec_get_mut(v, i, type_size);
	last = xft_vec_peek_last(v, type_size);
	if (elem == nullptr || last == nullptr)
		return ((t_result){.ok = KO, .err = xft_err_inval});
	xft_memmove(elem, elem + type_size, (t_uptr)last - (t_uptr)elem);
	v->buf.size -= type_size;
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(2)))
t_result	xft_vec_remove_managed(t_allocator allocator,
	t_vec *restrict const v, size_t i, size_t type_size)
{
	t_u8		*elem;
	const t_u8	*last;

	if (v->buf.mem == nullptr || allocator.allocator == nullptr
		|| allocator.vtable == nullptr || allocator.vtable->free == nullptr)
		__builtin_unreachable();
	elem = xft_vec_get_mut(v, i, type_size);
	last = xft_vec_peek_last(v, type_size);
	if (elem == nullptr || last == nullptr)
		return ((t_result){.ok = KO, .err = xft_err_inval});
	allocator.vtable->free(allocator.allocator, *(t_buffer *)elem);
	xft_memmove(elem, elem + type_size, (t_uptr)last - (t_uptr)elem);
	v->buf.size -= type_size;
	return ((t_result){.ok = OK});
}
