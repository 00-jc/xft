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

/* the fewest slots that take capacity inserts under the 85% rehash check */
__attribute__((__nonnull__(2)))
t_result	xft_new_indexmap_with(t_allocator allocator,
	t_indexmap *__restrict__ const map, t_size capacity)
{
	t_result	ret;

	if (__builtin_expect(capacity == 0, 0))
		return ((t_result){.ok = KO, .err = xft_err_inval});
	*map = (t_indexmap){0};
	ret = xft_new_soa(allocator, &map->soa,
			xft_next_pow2((capacity - 1) * 20 / 17 + 1), xft__imap_ctx());
	if (__builtin_expect(!ret.ok, 0))
		return (ret);
	xft_memset(xft__imap_meta(map), IMAP_EMPTY, map->soa.capacity_elements);
	return ((t_result){.ok = OK});
}

__attribute__((__nonnull__(2)))
t_result	xft_new_indexmap(t_allocator allocator,
	t_indexmap *__restrict__ const map)
{
	return (xft_new_indexmap_with(allocator, map, INDEXMAP_INITIAL_SIZE));
}

__attribute__((__nonnull__(1)))
void	xft_indexmap_clear(t_indexmap *__restrict__ const map)
{
	if (map->soa.ptr == nullptr)
		__builtin_unreachable();
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
