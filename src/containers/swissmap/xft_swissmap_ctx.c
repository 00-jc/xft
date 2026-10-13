/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_swissmap_ctx.c                                 :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 20:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 20:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_swissmap.h"

__attribute__((const, __always_inline__, __returns_nonnull__))
inline const t_soa_context	*xft__swiss_ctx(void)
{
	__extension__ static const t_soa_context	ctx = {
		.total_struct_size = sizeof(t_u8) + sizeof(t_buffer)
		+ sizeof(t_u8 *),
		.max_alignment = SWISS_GROUP,
		.fields_count = SWISS_FIELDS,
		.entries = {
	{.size = sizeof(t_u8), .size_of_prev_fields = 0,
		.offset_from_struct_base = __builtin_offsetof(t_swiss_slot, meta)},
	{.size = sizeof(t_buffer), .size_of_prev_fields = sizeof(t_u8),
		.offset_from_struct_base = __builtin_offsetof(t_swiss_slot, key)},
	{.size = sizeof(t_u8 *), .size_of_prev_fields = sizeof(t_u8)
		+ sizeof(t_buffer),
		.offset_from_struct_base = __builtin_offsetof(t_swiss_slot, value)},
	}};

	return (&ctx);
}
