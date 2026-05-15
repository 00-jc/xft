/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_insert_unchecked.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 02:32:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:25:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_map.h"

__attribute__((__nonnull__(1, 3)))
static inline void	ft__map_insert_unchecked(t_map *restrict const map,
	t_bucket entry, size_t data[3])
{
	t_u16a		mask;
	size_t		group;
	size_t		gg;
	size_t		i;

	if (map->meta == nullptr || map->buckets == nullptr)
		__builtin_unreachable();
	group = data[GROUP];
	while (1)
	{
		mask = ft_bitpack128(((t_blk128r)map->meta)[group] & 0x80);
		if (mask)
		{
			i = ft_memctz_u16(mask);
			gg = (group << 4) + i;
			map->meta[gg] = (t_u8)data[H2];
			map->buckets[gg] = entry;
			map->count++;
			return ;
		}
		group = (group + 1) % data[NBLK];
	}
}

__attribute__((__nonnull__(1, 2, 4)))
void	ft_map_insert_unchecked(t_map *restrict const map,
	t_u8 *restrict const key, size_t keylen,
	t_u8 *restrict const value)
{
	t_u64a		hash;
	size_t		nblks;
	t_bucket	entry;

	if (map->meta == nullptr || map->buckets == nullptr)
		__builtin_unreachable();
	hash = ft_xxh3_64bits(ft_fatptr(key, keylen), 0);
	nblks = map->table_size >> 4;
	entry = (t_bucket){
		.key = key,
		.key_len = keylen,
		.value = value,
	};
	ft__map_insert_unchecked(map, entry,
		(size_t [3]){(hash >> 57) & MAP_H2_MASK,
		nblks, hash % nblks});
}
