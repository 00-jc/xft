/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 21:46:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/19 22:59:22 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fibhashc.h"

__attribute__((__nonnull__(1), __pure__))
t_u64	fhc_load_span(const t_u8 *__restrict__ const p,
	t_u32 len)
{
	const t_u64a	zero = 0;
	const t_u8		*wide;
	const t_u8		*narrow;
	t_u32			woff;
	t_u32			noff;

	wide = (const t_u8 *)xft_tern(len >= 4, (t_u64a)p, (t_u64a) & zero);
	woff = (t_u32)xft_tern(len >= 4, len - 4, 0);
	narrow = (const t_u8 *)xft_tern(len >= 2, (t_u64a)p, (t_u64a) & zero);
	noff = (t_u32)xft_tern(len >= 2, len - 2, 0);
	return ((t_u64)(*p)
		| (t_u64)(*(t_blk16r)narrow)
		| (t_u64)(*(t_blk16r)(narrow + noff)) << (noff << 3)
		| (t_u64)(*(t_blk32r)wide)
		| (t_u64)(*(t_blk32r)(wide + woff)) << (woff << 3));
}
