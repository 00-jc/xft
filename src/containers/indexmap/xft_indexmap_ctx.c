/* ************************************************************************** */
/*                                                                            */
/*                                                     :::      ::::::::      */
/*   xft_indexmap_ctx.c                                 :+:      :+:    :+:   */
/*                                                 +:+ +:+         +:+        */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                             +#+#+#+#+#+   +#+              */
/*   Created: 2026/10/13 21:00:06 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/13 21:00:06 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_indexmap.h"

__attribute__((const, __always_inline__, __returns_nonnull__, __used__))
inline const t_soa_context	*xft__imap_ctx(void)
{
	__extension__ static const t_soa_context	ctx = {
		.total_struct_size = sizeof(t_u8) + sizeof(t_buffer)
		+ sizeof(t_size) + sizeof(t_u64a),
		.max_alignment = IMAP_GROUP,
		.fields_count = IMAP_FIELDS,
		.entries = {
	{.size = sizeof(t_u8), .size_of_prev_fields = 0,
		.offset_from_struct_base = __builtin_offsetof(t_imap_slot, meta)},
	{.size = sizeof(t_buffer), .size_of_prev_fields = sizeof(t_u8),
		.offset_from_struct_base = __builtin_offsetof(t_imap_slot, key)},
	{.size = sizeof(t_size), .size_of_prev_fields = sizeof(t_u8)
		+ sizeof(t_buffer),
		.offset_from_struct_base = __builtin_offsetof(t_imap_slot, value)},
	{.size = sizeof(t_u64a), .size_of_prev_fields = sizeof(t_u8)
		+ sizeof(t_buffer) + sizeof(t_size),
		.offset_from_struct_base = __builtin_offsetof(t_imap_slot, seed)},
	}};

	return (&ctx);
}
