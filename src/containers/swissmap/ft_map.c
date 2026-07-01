/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:20 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_map	ft_map_with(t_allocator allocator, t_size capacity)
{
	t_buffer	meta_buf;
	t_buffer	bucket_buf;

	if (capacity & 15)
		return ((t_map){0});
	meta_buf = allocator.interface.allocate(allocator.allocator,
			capacity, ft_next_pow2(capacity));
	if (meta_buf.mem == nullptr)
		return ((t_map){0});
	ft_memset(meta_buf.mem, MAP_EMPTY, capacity);
	bucket_buf = allocator.interface.allocate(allocator.allocator,
			capacity * sizeof(t_bucket),
			ft_next_pow2(capacity * sizeof(t_bucket)));
	if (bucket_buf.mem == nullptr)
		return (allocator.interface.free(allocator.allocator, meta_buf),
			(t_map){0});
	return ((t_map)
		{
			.buckets = (t_bucket *)bucket_buf.mem,
			.meta = meta_buf.mem,
			.bucket_buf = bucket_buf,
			.meta_buf = meta_buf,
			.count = 0,
			.table_size = capacity,
		});
}

__attribute__((__nonnull__(1)))
void	ft_map_clear(t_map *map)
{
	ft_memset(map->meta, MAP_EMPTY, map->table_size);
	map->count = 0;
}

t_map	ft_map_new(t_allocator allocator)
{
	return (ft_map_with(allocator, MAP_INITIAL_SIZE));
}

__attribute__((__nonnull__(2)))
void	ft_map_destroy(t_allocator allocator, t_map *restrict const map)
{
	allocator.interface.free(allocator.allocator, map->bucket_buf);
	allocator.interface.free(allocator.allocator, map->meta_buf);
}
