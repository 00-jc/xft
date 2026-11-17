/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_swissmap.c                                     :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/11/01 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_swissmap.h>

/* the fewest slots that take capacity inserts under the 85% rehash check */
__attribute__((__nonnull__(2)))
t_result	xft_new_swissmap_with(t_allocator allocator,
	t_swissmap *__restrict__ const map, t_size capacity)
{
	if (__builtin_expect(capacity == 0, 0))
		return (KO);
	*map = (t_swissmap){0};
	if (__builtin_expect(!xft_new_soa(allocator, &map->soa,
				xft_next_pow2((capacity - 1) * 20 / 17 + 1),
				xft__swiss_ctx()), 0))
		return (KO);
	xft_memset(xft__swiss_meta(map), SWISS_EMPTY, map->soa.capacity_elements);
	return (OK);
}

__attribute__((__nonnull__(2)))
t_result	xft_new_swissmap(t_allocator allocator,
	t_swissmap *__restrict__ const map)
{
	return (xft_new_swissmap_with(allocator, map, SWISS_INITIAL_SIZE));
}

__attribute__((__nonnull__(1)))
void	xft_swissmap_clear(t_swissmap *__restrict__ const map)
{
	if (map->soa.ptr == nullptr)
		__builtin_unreachable();
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
