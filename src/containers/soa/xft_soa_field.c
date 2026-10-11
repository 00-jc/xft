/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_soa_field.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 15:50:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/11 15:59:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "soa.h"

__attribute__((pure, __always_inline__,
	__nonnull__(1, 2), __returns_nonnull__))
inline void	*xft_soa_fields(const t_soa *__restrict__ const soa,
	const t_soa_context *__restrict__ const ctx,
	t_size field_idx)
{
	const t_u8 *__restrict__ const		base = soa->ptr;

	if (field_idx >= ctx->fields_count)
		__builtin_unreachable();
	return ((t_any)(base + (ctx->entries[field_idx].size_of_prev_fields
			* soa->capacity_elements)));
}
