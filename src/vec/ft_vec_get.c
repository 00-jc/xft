/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:14:07 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:30:12 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

__attribute__((__nonnull__(1), __always_inline__, pure))
inline const void	*ft_vec_get(const t_vec *restrict const vec,
		size_t idx, size_t type_size)
{
	return ((void *)(-(idx < vec->size)
		& ((t_uptr)vec->buf.mem + idx * type_size)));
}

__attribute__((__nonnull__(1), __always_inline__, pure))
inline void	*ft_vec_get_mut(const t_vec *restrict const vec,
		size_t idx, size_t type_size)
{
	return ((void *)(-(idx < vec->size)
		& ((t_uptr)vec->buf.mem + idx * type_size)));
}

__attribute__((__nonnull__(1), __always_inline__, pure))
inline const void	*ft_vec_peek_last(const t_vec *restrict const vec,
	size_t type_size)
{
	return ((const void *)(-((t_uptr)vec->size != 0)
		& ((t_uptr)vec->buf.mem + ((vec->size - 1) * type_size))));
}

__attribute__((__nonnull__(1), __always_inline__, pure))
inline void	*ft_vec_get_last(const t_vec *restrict const vec, size_t type_size)
{
	return ((t_u8 *)(-((t_uptr)vec->size != 0)
		& ((t_uptr)vec->buf.mem + ((vec->size - 1) * type_size))));
}
