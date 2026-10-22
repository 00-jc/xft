/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_indexmap_probe_seeded.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:52:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/22 12:54:01 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_indexmap.h"

__attribute__((__always_inline__, pure, __nonnull__(1)))
inline t_imap_probe	xft__imap_probe_seeded(
	const t_indexmap *__restrict__ const map, t_buffer key, t_u64a seed)
{
	const t_u64a	hash = xft_xxh3_64bits(key, seed);
	const t_size	nblks = map->soa.capacity_elements / IMAP_GROUP;

	return ((t_imap_probe){.h2 = (hash >> 57) & IMAP_H2_MASK,
		.nblks = nblks, .group = hash % nblks, .seed = seed});
}
