/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_indexmap_insert.c                              :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_indexmap.h>

__attribute__((__always_inline__, __unused__, __nonnull__(1)))
static inline void	xft__imap_insert_unchecked(
	t_indexmap *__restrict__ const map,
	t_imap_slot slot)
{
	const t_imap_probe	probe = xft__imap_probe_seeded(map, slot.key,
			slot.seed);

	xft__imap_set(map, xft__imap_find_free(map, probe), slot);
	++map->count;
}

__attribute__((__cold__, __noinline__, __unused__, __nonnull__(2)))
static t_result	xft__imap_rehash(t_allocator allocator,
	t_indexmap *__restrict__ const map)
{
	const t_size	cap = map->soa.capacity_elements;
	t_indexmap		new;
	t_imap_slot		slot;
	t_size			i;

	new = xft_new_indexmap_with(allocator,
			cap << (map->count * 40 >= cap * 17));
	if (__builtin_expect(new.soa.ptr == nullptr, 0))
		return (KO);
	i = 0;
	while (i < cap)
	{
		slot = xft__imap_get(map, i++);
		if (slot.meta <= IMAP_H2_MASK)
			xft__imap_insert_unchecked(&new, slot);
	}
	xft_destroy_soa(allocator, &map->soa);
	*map = new;
	return (OK);
}

__attribute__((__flatten__, __nonnull__(2)))
t_result	xft_indexmap_insert_seeded(t_allocator allocator,
	t_indexmap *__restrict__ const map,
	t_imap_key key, t_size value)
{
	t_imap_probe	probe;
	t_size			idx;

	if (__builtin_expect((map->count + map->tombstones) * 20
			>= map->soa.capacity_elements * 17, 0)
		&& !xft__imap_rehash(allocator, map))
		return (KO);
	probe = xft__imap_probe_seeded(map, key.key, key.seed);
	idx = xft__imap_find(map, key.key, probe);
	if (idx == INDEXMAP_NPOS)
	{
		idx = xft__imap_find_free(map, probe);
		map->tombstones -= (xft__imap_meta(map)[idx] == IMAP_DELETED);
		++map->count;
	}
	xft__imap_set(map, idx, (t_imap_slot){.meta = probe.h2,
		.key = key.key, .value = value, .seed = key.seed});
	return (OK);
}

__attribute__((__flatten__, __nonnull__(2)))
t_result	xft_indexmap_insert(t_allocator allocator,
	t_indexmap *__restrict__ const map,
	t_buffer key, t_size value)
{
	return (xft_indexmap_insert_seeded(allocator, map,
			(t_imap_key){.key = key, .seed = 0}, value));
}
