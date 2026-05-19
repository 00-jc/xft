/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 21:35:17 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/17 03:11:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memcpy_128(void *restrict dest,
	const void	*restrict const src, size_t n)
{
	t_vu128a		x[2];

	x[0] = ((t_blk128r)src)[0];
	x[1] = *((t_blk128r)ft_overlap(src, sizeof(t_vu128a), n));
	*((t_blk128w)dest) = x[0];
	*((t_blk128w)ft_overlap(dest, sizeof(t_vu128a), n)) = x[1];
}
