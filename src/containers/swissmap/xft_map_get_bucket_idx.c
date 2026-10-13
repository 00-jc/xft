/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_map_get_bucket_idx.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 18:39:29 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

__attribute__((__nonnull__(1, 2, 3)))
static inline t_size	xft__map_idx(const t_map *restrict const map,
	const t_u8 *restrict const mem, t_size data[4])
{
	t_vu128		sse;
	t_u16a		mask;
	t_bucket	bucket;
	t_size		i;
	t_u8		h2;

	h2 = (t_u8)data[H2];
	sse = ((t_blk128ra)map->meta)[data[GROUP]];
	while (1)
	{
		mask = xft_vmask128((t_vu128)(sse == h2));
		while (mask)
		{
			i = xft_memctz_u16(mask);
			bucket = map->buckets[(data[GROUP] << 4) + i];
			if (bucket.key_len == data[SIZE]
				&& !xft_memcmp(mem, bucket.key, bucket.key_len))
				return ((data[GROUP] << 4) + i);
			mask &= mask - 1;
		}
		if ((t_u128a)(sse == 0xFF))
			__builtin_unreachable();
		data[GROUP] = (data[GROUP] + 1) % data[NBLK];
		sse = ((t_blk128r)map->meta)[data[GROUP]];
	}
}

// invariant: element has to exist in the table.

__attribute__((__nonnull__(1), pure))
t_size	xft_map_get_bucket_idx(const t_map *restrict const map, t_buffer key)
{
	t_u64a		hash;
	t_u8		h2;
	t_size		group;
	t_size		nblks;

	if (map->buckets == nullptr || map->meta == nullptr)
		__builtin_unreachable();
	hash = xft_xxh3_64bits(key, 0);
	h2 = (hash >> 57) & MAP_H2_MASK;
	nblks = map->table_size >> 4;
	group = hash % nblks;
	return (xft__map_idx(map, key.mem,
			(t_size [4]){h2, nblks, group, key.size}));
}
