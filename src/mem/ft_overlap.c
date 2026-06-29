/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overlap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 01:22:26 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/12 19:04:25 by jaicastr         ###   ########.fr       */
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
