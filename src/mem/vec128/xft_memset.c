/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1), __always_inline__, __used__))
inline void	xft_memset_128(t_any restrict dest,
	const t_u8 c, t_size n)
{
	register t_vu128a	x;

	x = (t_vu128a){c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c};
	*(t_blk128w)dest = x;
	*(t_blk128w)xft_overlap(dest, sizeof(t_vu128a), n) = x;
}
