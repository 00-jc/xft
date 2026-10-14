/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_indexmap_delete.c                              :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_indexmap.h"

__attribute__((__flatten__, __nonnull__(1)))
t_size	xft_indexmap_delete(t_indexmap *__restrict__ const map,
	t_buffer key)
{
	t_u8 *const		meta = xft__imap_meta(map);
	const t_size	idx = xft__imap_find(map, key,
			xft__imap_probe(map, key));

	if (idx == INDEXMAP_NPOS)
		return (INDEXMAP_NPOS);
	--map->count;
	if (xft_veqmask(((t_blknra)meta)[idx / IMAP_GROUP], IMAP_EMPTY))
		meta[idx] = IMAP_EMPTY;
	else
	{
		meta[idx] = IMAP_DELETED;
		++map->tombstones;
	}
	return (((t_size *)xft_soa_fields(&map->soa, xft__imap_ctx(),
				IMAP_VALUE))[idx]);
}
