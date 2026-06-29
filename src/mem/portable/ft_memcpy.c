/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 21:35:17 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/14 00:42:36 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memcpy_64(void *restrict dest,
	const void	*restrict const src, t_size n)
{
	t_u64a		x[2];

	x[0] = ((t_blk64r)src)[0];
	x[1] = *((t_blk64r)ft_overlap(src, sizeof(t_u64a), n));
	((t_blk64w)dest)[0] = x[0];
	*((t_blk64w)ft_overlap(dest, sizeof(t_u64a), n)) = x[1];
}
