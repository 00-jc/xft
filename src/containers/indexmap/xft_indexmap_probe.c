/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_indexmap_probe.c                               :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_indexmap.h"

__attribute__((__always_inline__, pure, __nonnull__(1)))
inline t_imap_probe	xft__imap_probe(
	const t_indexmap *__restrict__ const map, t_buffer key)
{
	const t_u64a	hash = xft_xxh3_64bits(key, 0);
	const t_size	nblks = map->soa.capacity_elements / IMAP_GROUP;

	return ((t_imap_probe){.h2 = (hash >> 57) & IMAP_H2_MASK,
		.nblks = nblks, .group = hash % nblks});
}

__attribute__((__always_inline__, pure, __nonnull__(1)))
static inline t_result	xft__imap_key_eq(
	const t_soa *__restrict__ const soa, t_size idx, t_buffer key)
{
	const t_buffer *const	keys = xft_soa_fields(soa, xft__imap_ctx(),
			IMAP_KEY);

	return (keys[idx].size == key.size
		&& !xft_memcmp(key.mem, keys[idx].mem, key.size));
}

__attribute__((__always_inline__, pure, __nonnull__(1)))
inline t_size	xft__imap_find(const t_indexmap *__restrict__ const map,
	t_buffer key, t_imap_probe probe)
{
	const t_u8 *const	meta = xft__imap_meta(map);
	t_nvec				vec;
	t_nmask				mask;
	t_size				idx;

	while (1)
	{
		vec = ((t_blknra)meta)[probe.group];
		mask = xft_veqmask(vec, probe.h2);
		while (mask)
		{
			idx = probe.group * IMAP_GROUP + xft_memctz_u64(mask);
			if (xft__imap_key_eq(&map->soa, idx, key))
				return (idx);
			mask &= mask - 1;
		}
		if (xft_veqmask(vec, IMAP_EMPTY))
			return (INDEXMAP_NPOS);
		probe.group = (probe.group + 1) % probe.nblks;
	}
}

__attribute__((__always_inline__, pure, __nonnull__(1)))
inline t_size	xft__imap_find_free(const t_indexmap *__restrict__ const map,
	t_imap_probe probe)
{
	const t_u8 *const	meta = xft__imap_meta(map);
	t_nmask				mask;

	while (1)
	{
		mask = xft_vmask(((t_blknra)meta)[probe.group]);
		if (mask)
			return (probe.group * IMAP_GROUP + xft_memctz_u64(mask));
		probe.group = (probe.group + 1) % probe.nblks;
	}
}
