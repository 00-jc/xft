/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_p_swissmap_probe.h                             :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_SWISSMAP_PROBE_H
# define XFT_P_SWISSMAP_PROBE_H

# include "xft_p_swissmap_slot.h"

__attribute__((__always_inline__, __unused__, pure, __nonnull__(1)))
static inline t_swiss_probe	xft__swiss_probe(
	const t_swissmap *__restrict__ const map, t_buffer key)
{
	const t_u64a	hash = xft_xxh3_64bits(key, 0);
	const t_size	nblks = map->soa.capacity_elements / SWISS_GROUP;

	return ((t_swiss_probe){.h2 = (hash >> 57) & SWISS_H2_MASK,
		.nblks = nblks, .group = hash % nblks});
}

__attribute__((__always_inline__, __unused__, pure, __nonnull__(1)))
static inline t_result	xft__swiss_key_eq(
	const t_soa *__restrict__ const soa, t_size idx, t_buffer key)
{
	const t_buffer *const	keys = xft_soa_fields(soa, xft__swiss_ctx(),
			SWISS_KEY);

	return (keys[idx].size == key.size
		&& !xft_memcmp(key.mem, keys[idx].mem, key.size));
}

__attribute__((__always_inline__, __unused__, pure, __nonnull__(1)))
static inline t_size	xft__swiss_find(
	const t_swissmap *__restrict__ const map, t_buffer key,
	t_swiss_probe probe)
{
	const t_u8 *const	meta = xft__swiss_meta(map);
	t_vu128				sse;
	t_u16a				mask;
	t_size				idx;

	while (1)
	{
		sse = ((t_blk128ra)meta)[probe.group];
		mask = xft_vmask128((t_vu128)(sse == probe.h2));
		while (mask)
		{
			idx = probe.group * SWISS_GROUP + xft_memctz_u16(mask);
			if (xft__swiss_key_eq(&map->soa, idx, key))
				return (idx);
			mask &= mask - 1;
		}
		if (xft_vmask128((t_vu128)(sse == SWISS_EMPTY)))
			return (SWISS_NPOS);
		probe.group = (probe.group + 1) % probe.nblks;
	}
}

__attribute__((__always_inline__, __unused__, pure, __nonnull__(1)))
static inline t_size	xft__swiss_find_free(
	const t_swissmap *__restrict__ const map, t_swiss_probe probe)
{
	const t_u8 *const	meta = xft__swiss_meta(map);
	t_u16a				mask;

	while (1)
	{
		mask = xft_vmask128(((t_blk128ra)meta)[probe.group]);
		if (mask)
			return (probe.group * SWISS_GROUP + xft_memctz_u16(mask));
		probe.group = (probe.group + 1) % probe.nblks;
	}
}

#endif
