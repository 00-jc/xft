/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overlap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/*
 *	Invariant: ptr - chunk_size must be valid data
 */

__attribute__((__always_inline__, __nonnull__(1), __const__))
inline void	*ft_overlap(const void *restrict ptr,
	t_size chunk_size, t_size rem_size)
{
	return ((((t_u8 *)ptr) + rem_size) - chunk_size);
}
