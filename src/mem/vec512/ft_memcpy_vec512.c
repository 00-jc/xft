/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_vec512.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__))
inline void	ft_memcpy_512(void *restrict dest,
	const void	*restrict const src, t_size n)
{
	t_vu512a		x[2];

	x[0] = ((t_blk512r)src)[0];
	x[1] = *((t_blk512r)ft_overlap(src, sizeof(t_vu512a), n));
	*((t_blk512w)dest) = x[0];
	*((t_blk512w)ft_overlap(dest, sizeof(t_vu512a), n)) = x[1];
}
