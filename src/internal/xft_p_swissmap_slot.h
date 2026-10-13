/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_p_swissmap_slot.h                              :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_SWISSMAP_SLOT_H
# define XFT_P_SWISSMAP_SLOT_H

# include "xft_p_swissmap.h"

__attribute__((__always_inline__, __unused__, pure, __nonnull__(1),
	__returns_nonnull__))
static inline t_u8	*xft__swiss_meta(const t_swissmap *__restrict__ const map)
{
	return (xft_soa_fields(&map->soa, xft__swiss_ctx(), SWISS_META));
}

__attribute__((__always_inline__, __unused__, __nonnull__(1)))
static inline void	xft__swiss_set(t_swissmap *__restrict__ const map,
	t_size idx, t_swiss_slot slot)
{
	const t_soa_context *const	ctx = xft__swiss_ctx();

	xft__swiss_meta(map)[idx] = slot.meta;
	((t_buffer *)xft_soa_fields(&map->soa, ctx, SWISS_KEY))[idx] = slot.key;
	((t_u8 **)xft_soa_fields(&map->soa, ctx, SWISS_VALUE))[idx] = slot.value;
}

__attribute__((__always_inline__, __unused__, pure, __nonnull__(1)))
static inline t_swiss_slot	xft__swiss_get(
	const t_swissmap *__restrict__ const map, t_size idx)
{
	const t_soa_context *const	ctx = xft__swiss_ctx();

	return ((t_swiss_slot){
		.meta = xft__swiss_meta(map)[idx],
		.key = ((t_buffer *)xft_soa_fields(&map->soa, ctx, SWISS_KEY))[idx],
		.value = ((t_u8 **)xft_soa_fields(&map->soa, ctx, SWISS_VALUE))[idx],
	});
}

#endif
