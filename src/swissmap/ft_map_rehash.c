/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_rehash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 02:47:51 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 11:29:26 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_map.h"

__attribute__((__nonnull__(2)))
t_u32a	ft_map_rehash(t_allocator allocator, t_map *restrict const map)
{
	t_map	new;
	size_t	i;

	if (map->buckets == nullptr || map->meta == nullptr)
		__builtin_unreachable();
	new = ft_map_with(allocator, map->table_size << 1);
	if (!new.meta || !new.buckets)
		return (0);
	i = 0;
	while (i < map->table_size)
	{
		if (map->meta[i] <= MAP_H2_MASK)
			ft_map_insert_unchecked(&new,
				ft_fatptr(map->buckets[i].key, map->buckets[i].key_len),
				map->buckets[i].value);
		++i;
	}
	allocator.interface.free(allocator.allocator, map->meta_buf);
	allocator.interface.free(allocator.allocator, map->bucket_buf);
	*map = new;
	return (1);
}
