/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_indexmap_lookup.c                              :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_indexmap.h"

__attribute__((__flatten__, pure, __nonnull__(1)))
t_size	xft_indexmap_lookup(const t_indexmap *__restrict__ const map,
	t_buffer key)
{
	const t_size	idx = xft__imap_find(map, key,
			xft__imap_probe(map, key));

	if (idx == INDEXMAP_NPOS)
		return (INDEXMAP_NPOS);
	return (((t_size *)xft_soa_fields(&map->soa, xft__imap_ctx(),
				IMAP_VALUE))[idx]);
}
