/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_swissmap_insert.c                              :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/06/29 23:39:14 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_swissmap.h>

__attribute__((__always_inline__, __unused__, __nonnull__(1, 3)))
static inline void	xft__swiss_insert_unchecked(
	t_swissmap *__restrict__ const map,
	t_buffer key, t_u8 *__restrict__ const value)
{
	const t_swiss_probe	probe = xft__swiss_probe(map, key);

	xft__swiss_set(map, xft__swiss_find_free(map, probe),
		(t_swiss_slot){.meta = probe.h2, .key = key, .value = value});
	++map->count;
}

__attribute__((__cold__, __noinline__, __unused__, __nonnull__(2)))
static t_result	xft__swiss_rehash(t_allocator allocator,
	t_swissmap *__restrict__ const map)
{
	const t_size	cap = map->soa.capacity_elements;
	t_swissmap		new;
	t_swiss_slot	slot;
	t_size			i;

	new = xft_new_swissmap_with(allocator,
			cap << (map->count * 40 >= cap * 17));
	if (__builtin_expect(new.soa.ptr == nullptr, 0))
		return (KO);
	i = 0;
	while (i < cap)
	{
		slot = xft__swiss_get(map, i++);
		if (slot.meta <= SWISS_H2_MASK)
			xft__swiss_insert_unchecked(&new, slot.key, slot.value);
	}
	xft_destroy_soa(allocator, &map->soa);
	*map = new;
	return (OK);
}

__attribute__((__flatten__, __nonnull__(2, 4)))
t_result	xft_swissmap_insert(t_allocator allocator,
	t_swissmap *__restrict__ const map,
	t_buffer key, t_u8 *__restrict__ const value)
{
	t_swiss_probe	probe;
	t_size			idx;

	if (__builtin_expect((map->count + map->tombstones) * 20
			>= map->soa.capacity_elements * 17, 0)
		&& !xft__swiss_rehash(allocator, map))
		return (KO);
	probe = xft__swiss_probe(map, key);
	idx = xft__swiss_find(map, key, probe);
	if (idx == SWISS_NPOS)
	{
		idx = xft__swiss_find_free(map, probe);
		map->tombstones -= (xft__swiss_meta(map)[idx] == SWISS_DELETED);
		++map->count;
	}
	xft__swiss_set(map, idx, (t_swiss_slot){.meta = probe.h2,
		.key = key, .value = value});
	return (OK);
}
