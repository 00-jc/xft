/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_memcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 12:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/16 01:43:38 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_mem.h"

__attribute__((__nonnull__(1, 2), __always_inline__, __hot__,
	__returns_nonnull__))
inline void	*xft_memcpy(t_any restrict dest,
	t_cany restrict const src, t_size n)
{
	if (n == 1)
		return ((void)(*(t_blk8w)dest = *(t_blk8w)src), dest);
	if (n == 2)
		return ((void)(*(t_blk16w)dest = *(t_blk16w)src), dest);
	if (n == 4)
		return ((void)(*(t_blk32w)dest = *(t_blk32w)src), dest);
	if (n == 8)
		return ((void)(*(t_blk64w)dest = *(t_blk64w)src), dest);
	if (n == 16)
		return ((void)(*(t_blk128w)dest = *(t_blk128w)src), dest);
	if (n == 32)
		return ((void)(*(t_blk256w)dest = *(t_blk256w)src), dest);
	if (n == 64)
		return ((void)(*(t_blk512w)dest = *(t_blk512w)src), dest);
	return (xft__memcpy(dest, src, n));
}
