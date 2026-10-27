/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_indexmap.c                                     :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_indexmap.h>

t_indexmap	xft_new_indexmap_with(t_allocator allocator, t_size capacity)
{
	t_indexmap	map;

	if (capacity == 0 || (capacity & (IMAP_GROUP - 1)))
		return ((t_indexmap){0});
	map = (t_indexmap){.soa = xft_new_soa(allocator, capacity,
			xft__imap_ctx())};
	if (__builtin_expect(map.soa.ptr == nullptr, 0))
		return (map);
	xft_memset(xft__imap_meta(&map), IMAP_EMPTY, map.soa.capacity_elements);
	return (map);
}

t_indexmap	xft_new_indexmap(t_allocator allocator)
{
	return (xft_new_indexmap_with(allocator, INDEXMAP_INITIAL_SIZE));
}

__attribute__((__nonnull__(1)))
void	xft_indexmap_clear(t_indexmap *__restrict__ const map)
{
	if (map->soa.ptr == nullptr)
		return ;
	xft_memset(xft__imap_meta(map), IMAP_EMPTY, map->soa.capacity_elements);
	map->count = 0;
	map->tombstones = 0;
}

__attribute__((__nonnull__(2)))
void	xft_indexmap_destroy(t_allocator allocator,
	t_indexmap *__restrict__ const map)
{
	xft_destroy_soa(allocator, &map->soa);
	*map = (t_indexmap){0};
}
