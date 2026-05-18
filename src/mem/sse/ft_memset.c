/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 21:35:17 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 21:15:42 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_mem.h"

__attribute__((__nonnull__(1), __always_inline__))
inline void	ft_memset_128(void *restrict dest,
	const t_u8 c, size_t n)
{
	register t_vu128a	x;

	x = (t_vu128a){c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};
	*(t_blk128w)dest = x;
	*(t_blk128w)ft_overlap(dest, sizeof(t_vu128a), n) = x;
}
