/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_swissmap.c                                     :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_swissmap_slot.h"

t_swissmap	xft_new_swissmap_with(t_allocator allocator, t_size capacity)
{
	t_swissmap	map;

	if (capacity == 0 || (capacity & (SWISS_GROUP - 1)))
		return ((t_swissmap){0});
	map = (t_swissmap){.soa = xft_new_soa(allocator, capacity,
			xft__swiss_ctx())};
	if (__builtin_expect(map.soa.ptr == nullptr, 0))
		return (map);
	xft_memset(xft__swiss_meta(&map), SWISS_EMPTY, map.soa.capacity_elements);
	return (map);
}

t_swissmap	xft_new_swissmap(t_allocator allocator)
{
	return (xft_new_swissmap_with(allocator, SWISS_INITIAL_SIZE));
}

__attribute__((__nonnull__(1)))
void	xft_swissmap_clear(t_swissmap *__restrict__ const map)
{
	if (map->soa.ptr == nullptr)
		return ;
	xft_memset(xft__swiss_meta(map), SWISS_EMPTY, map->soa.capacity_elements);
	map->count = 0;
	map->tombstones = 0;
}

__attribute__((__nonnull__(2)))
void	xft_swissmap_destroy(t_allocator allocator,
	t_swissmap *__restrict__ const map)
{
	xft_destroy_soa(allocator, &map->soa);
	*map = (t_swissmap){0};
}
