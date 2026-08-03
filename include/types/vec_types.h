/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 12:59:10 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_TYPES_H
# define VEC_TYPES_H

# include "primitives.h"

/// \brief Owned, growable, type-erased array; the vec.h functions take the
/// element size explicitly since t_vec itself does not store it.
/// \note `size` and `buf.size` are **byte** counts, not element counts —
/// divide by the element's `type_size` (e.g. via ft_vec_len) to get the
/// element count. `buf` is the allocator-owned backing storage; `size` is
/// the number of bytes currently in use, `buf.size` is the capacity.
typedef struct s_vec
{
	size_t		size;
	t_buffer	buf;
}	t_vec;

#endif
