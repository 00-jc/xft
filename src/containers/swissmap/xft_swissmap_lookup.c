/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_swissmap_lookup.c                              :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_swissmap.h>

__attribute__((__flatten__, pure, __nonnull__(1)))
t_any	xft_swissmap_lookup(const t_swissmap *__restrict__ const map,
	t_buffer key)
{
	const t_size	idx = xft__swiss_find(map, key,
			xft__swiss_probe(map, key));

	if (idx == SWISS_NPOS)
		return (nullptr);
	return (((t_u8 **)xft_soa_fields(&map->soa, xft__swiss_ctx(),
				SWISS_VALUE))[idx]);
}
