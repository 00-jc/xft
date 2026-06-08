/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_lookup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 02:35:25 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/08 03:04:17 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

__attribute__((__nonnull__(1, 2, 3)))
static inline void	*ft__map_lookup(const t_map *restrict const map,
	const t_u8 *restrict const mem, size_t data[4])
{
	t_vu128		sse;
	t_u16a		mask;
	t_bucket	bucket;
	size_t		i;
	t_u8		h2;

	h2 = (t_u8)data[H2];
	sse = ((t_blk128ra)map->meta)[data[GROUP]];
	while (1)
	{
		mask = ft_bitpack128((t_vu128)(sse == h2));
		while (mask)
		{
			i = ft_memctz_u16(mask);
			bucket = map->buckets[(data[GROUP] << 4) + i];
			if (bucket.key_len == data[SIZE]
				&& !ft_memcmp(mem, bucket.key, bucket.key_len))
				return (bucket.value);
			mask &= mask - 1;
		}
		if ((t_u128a)(sse == 0xFF))
			return (nullptr);
		data[GROUP] = (data[GROUP] + 1) % data[NBLK];
		sse = ((t_blk128r)map->meta)[data[GROUP]];
	}
}

__attribute__((__nonnull__(1)))
void	*ft_map_lookup(const t_map *restrict const map, t_buffer key)
{
	t_u128a		hash;
	t_u8		h2;
	size_t		group;
	size_t		nblks;

	if (map->buckets == nullptr || map->meta == nullptr)
		__builtin_unreachable();
	hash = ft_xxh3_64bits(key, 0);
	h2 = (hash >> 57) & MAP_H2_MASK;
	nblks = map->table_size >> 4;
	group = hash % nblks;
	return (ft__map_lookup(map, key.mem,
			(size_t [4]){h2, nblks, group, key.size}));
}
