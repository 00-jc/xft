/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 13:24:04 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(1), __always_inline__, pure))
inline const void	*ft_vec_get(const t_vec *restrict const vec,
		size_t idx, size_t type_size)
{
	t_size		byte_idx;

	byte_idx = idx * type_size;
	return ((void *)(-(byte_idx < vec->size)
		& ((t_uptr)vec->buf.mem + byte_idx)));
}

__attribute__((__nonnull__(1), __always_inline__, pure))
inline void	*ft_vec_get_mut(const t_vec *restrict const vec,
		size_t idx, size_t type_size)
{
	t_size	byte_idx;

	byte_idx = idx * type_size;
	return ((void *)(-(byte_idx < vec->size)
		& ((t_uptr)vec->buf.mem + byte_idx)));
}

__attribute__((__nonnull__(1), __always_inline__, pure))
inline const void	*ft_vec_peek_last(const t_vec *restrict const vec,
	size_t type_size)
{
	return ((const void *)(-((t_uptr)vec->size != 0)
		& ((t_uptr)vec->buf.mem + (vec->size - type_size))));
}

__attribute__((__nonnull__(1), __always_inline__, pure))
inline void	*ft_vec_get_last(const t_vec *restrict const vec, size_t type_size)
{
	return ((void *)(-((t_uptr)vec->size != 0)
		& ((t_uptr)vec->buf.mem + (vec->size - type_size))));
}
