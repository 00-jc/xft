/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_indexmap_get_arrays.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 15:03:50 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/22 15:15:38 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_indexmap.h"

__attribute__((pure, __returns_nonnull__, __always_inline__,
	used, __nonnull__(1)))
t_u8	*xft_indexmap_meta(const t_indexmap *__restrict__ const indexmap)
{
	return (xft_soa_fields(&indexmap->soa, xft__imap_ctx(), 0));
}

__attribute__((pure, __returns_nonnull__, __always_inline__,
	used, __nonnull__(1)))
t_u64a	*xft_indexmap_seed(const t_indexmap *__restrict__ const indexmap)
{
	return (xft_soa_fields(&indexmap->soa, xft__imap_ctx(), 3));
}
