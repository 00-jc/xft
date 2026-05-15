/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 22:43:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 19:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_map	ft_map_with(size_t capacity)
{
	t_buffer	meta_buf;
	t_buffer	bucket_buf;

	if (capacity & 15)
		return ((t_map){0});
	meta_buf = ft_palloc(capacity);
	if (meta_buf.mem == MAP_FAILED)
		return ((t_map){0});
	ft_memset(meta_buf.mem, MAP_EMPTY, capacity);
	bucket_buf = ft_palloc(capacity * sizeof(t_bucket));
	if (bucket_buf.mem == MAP_FAILED)
		return (ft_palloc_free(meta_buf), (t_map){0});
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

t_map	ft_map_new(void)
{
	return (ft_map_with(MAP_INITIAL_SIZE));
}

__attribute__((__nonnull__(1)))
void	ft_map_destroy(t_map *restrict const map)
{
	ft_palloc_free(map->bucket_buf);
	ft_palloc_free(map->meta_buf);
}
