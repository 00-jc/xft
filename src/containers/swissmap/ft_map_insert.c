/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 02:53:03 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/08 03:04:47 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "private/ft_p_map.h"

__attribute__((pure, __nonnull__(1)))
static inline size_t	ft__get_empty(const t_map *restrict const map,
	size_t group, size_t nblks)
{
	t_u16a		mask;

	if (map->meta == nullptr || map->buckets == nullptr)
		__builtin_unreachable();
	while (1)
	{
		mask = ft_bitpack128(
				(t_vu128)(((t_blk128ra)map->meta)[group] >= 0x80)
				);
		if (mask)
			return ((group << 4) + ft_memctz_u16(mask));
		group = (group + 1) % nblks;
	}
}

__attribute__((__always_inline__, __nonnull__(1)))
static inline void	ft__interbuck(t_map *restrict const map,
	t_bucket buck, size_t empty_lot, t_u128a hash)
{
	map->buckets[empty_lot] = buck;
	map->meta[empty_lot] = (hash >> 57) & MAP_H2_MASK;
}

__attribute__((__nonnull__(2, 4)))
t_result	ft_map_insert(t_allocator allocator, t_map *restrict const map,
	t_buffer key, t_u8 *restrict const value)
{
	size_t		empty_lot;
	t_bucket	buck;
	t_u64a		hash;
	size_t		nblks;
	size_t		group;

	if (((t_f64)map->count / (t_f64)map->table_size >= 0.85)
		&& !ft_map_rehash(allocator, map))
		return (KO);
	hash = ft_xxh3_64bits(key, 0);
	nblks = map->table_size >> 4;
	group = hash % nblks;
	empty_lot = ft__map_lookup_offset(map, key.mem,
			(size_t [4]){(hash >> 57) & MAP_H2_MASK, nblks, group, key.size});
	buck = (t_bucket){
		.key = key.mem,
		.key_len = key.size,
		.value = value,
	};
	if (empty_lot <= map->table_size)
		return (ft__interbuck(map, buck, empty_lot, hash), OK);
	empty_lot = ft__get_empty(map, group, nblks);
	ft__interbuck(map, buck, empty_lot, hash);
	map->count++;
	return (OK);
}
