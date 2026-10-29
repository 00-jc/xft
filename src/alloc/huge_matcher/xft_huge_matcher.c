/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_huge_matcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 01:29:43 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_hugepage.h>

#if defined(__linux__)

# include <xft/xft_p_syscalls.h>

__attribute__((__always_inline__, const))
static inline t_size	xft_snap_tier(t_size size, t_size tier, t_size page)
{
	return (xft_tern_s(tier - size <= tier >> 3, tier, page));
}

__attribute__((__always_inline__, const, __used__))
inline t_size	xft_match_hugepage(t_size requested_size)
{
	t_size	page_size;

	page_size = (requested_size + 4095) & ~(t_size)4095;
	page_size = xft_snap_tier(requested_size, HUGEPAGE_2MB, page_size);
	page_size = xft_snap_tier(requested_size, HUGEPAGE_8MB, page_size);
	page_size = xft_snap_tier(requested_size, HUGEPAGE_16MB, page_size);
	page_size = xft_snap_tier(requested_size, HUGEPAGE_256MB, page_size);
	page_size = xft_snap_tier(requested_size, HUGEPAGE_512MB, page_size);
	page_size = xft_snap_tier(requested_size, HUGEPAGE_1GB, page_size);
	page_size = xft_snap_tier(requested_size, HUGEPAGE_2GB, page_size);
	page_size = xft_snap_tier(requested_size, HUGEPAGE_MAX, page_size);
	page_size = xft_tern_s(requested_size <= 1048576,
			xft_next_pow2(requested_size), page_size);
	return (xft_tern_s(page_size < 8, 8, page_size));
}

__attribute__((__always_inline__, const, __used__))
inline t_result	xft_is_hugepage(t_u64 page_size)
{
	return ((t_result)((page_size == HUGEPAGE_2MB)
		| (page_size == HUGEPAGE_8MB)
		| (page_size == HUGEPAGE_16MB)
		| (page_size == HUGEPAGE_256MB)
		| (page_size == HUGEPAGE_512MB)
		| (page_size == HUGEPAGE_1GB)
		| (page_size == HUGEPAGE_2GB)
		| (page_size == HUGEPAGE_16GB)));
}

#endif
