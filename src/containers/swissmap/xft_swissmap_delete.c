/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_swissmap_delete.c                              :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_swissmap.h>

__attribute__((__flatten__, __nonnull__(1)))
void	xft_swissmap_delete(t_swissmap *__restrict__ const map,
	t_buffer key)
{
	const t_blk8wcl	meta = xft__swiss_meta(map);
	const t_size	idx = xft__swiss_find(map, key,
			xft__swiss_probe(map, key));

	if (idx == SWISS_NPOS)
		return ;
	--map->count;
	if (xft_veqmask(((t_blknra)meta)[idx / SWISS_GROUP], SWISS_EMPTY))
	{
		meta[idx] = SWISS_EMPTY;
		return ;
	}
	meta[idx] = SWISS_DELETED;
	++map->tombstones;
}
