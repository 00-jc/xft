/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_indexmap_slot.c                                :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_indexmap.h>

__attribute__((__always_inline__, pure, __nonnull__(1), __returns_nonnull__,
	__used__))
inline t_u8	*xft__imap_meta(const t_indexmap *__restrict__ const map)
{
	return (xft_soa_fields(&map->soa, xft__imap_ctx(), IMAP_META));
}

__attribute__((__always_inline__, __nonnull__(1), __used__))
inline void	xft__imap_set(t_indexmap *__restrict__ const map,
	t_size idx, t_imap_slot slot)
{
	const t_soa_context *const	ctx = xft__imap_ctx();

	xft__imap_meta(map)[idx] = slot.meta;
	((t_buffer *)xft_soa_fields(&map->soa, ctx, IMAP_KEY))[idx] = slot.key;
	((t_size *)xft_soa_fields(&map->soa, ctx, IMAP_VALUE))[idx] = slot.value;
	((t_u64a *)xft_soa_fields(&map->soa, ctx, IMAP_SEED))[idx] = slot.seed;
}

__attribute__((__always_inline__, pure, __nonnull__(1), __used__))
inline t_imap_slot	xft__imap_get(const t_indexmap *__restrict__ const map,
	t_size idx)
{
	const t_soa_context *const	ctx = xft__imap_ctx();

	return ((t_imap_slot){
		.meta = xft__imap_meta(map)[idx],
		.key = ((t_buffer *)xft_soa_fields(&map->soa, ctx, IMAP_KEY))[idx],
		.value = ((t_size *)xft_soa_fields(&map->soa, ctx, IMAP_VALUE))[idx],
		.seed = ((t_u64a *)xft_soa_fields(&map->soa, ctx, IMAP_SEED))[idx],
	});
}
