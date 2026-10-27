/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_huge_matcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/10 21:18:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_hugepage.h>

#if defined(__linux__)
# include <xft/xft_p_syscalls.h>
#endif

__attribute__((__always_inline__, const, __used__))
inline t_size	xft_match_hugepage(t_size requested_size)
{
	t_size	page_size;

	page_size = (-(requested_size <= HUGEPAGE_16GB) & HUGEPAGE_16GB)
		| (-(requested_size > HUGEPAGE_16GB) & requested_size);
	page_size = (-(requested_size <= HUGEPAGE_2GB) & HUGEPAGE_2GB)
		| (-(requested_size > HUGEPAGE_2GB) & page_size);
	page_size = (-(requested_size <= HUGEPAGE_1GB) & HUGEPAGE_1GB)
		| (-(requested_size > HUGEPAGE_1GB) & page_size);
	page_size = (-(requested_size <= HUGEPAGE_512MB) & HUGEPAGE_512MB)
		| (-(requested_size > HUGEPAGE_512MB) & page_size);
	page_size = (-(requested_size <= HUGEPAGE_256MB) & HUGEPAGE_256MB)
		| (-(requested_size > HUGEPAGE_256MB) & page_size);
	page_size = (-(requested_size <= HUGEPAGE_16MB) & HUGEPAGE_16MB)
		| (-(requested_size > HUGEPAGE_16MB) & page_size);
	page_size = (-(requested_size <= HUGEPAGE_8MB) & HUGEPAGE_8MB)
		| (-(requested_size > HUGEPAGE_8MB) & page_size);
	page_size = (-(requested_size <= HUGEPAGE_2MB) & HUGEPAGE_2MB)
		| (-(requested_size > HUGEPAGE_2MB) & page_size);
	page_size = xft_tern(requested_size <= 1048576,
			xft_next_pow2(requested_size), page_size);
	return (xft_tern(page_size < 8, 8, page_size));
}

#if defined(__linux__)

__attribute__((__always_inline__, const, __used__))
inline int	xft_match_hugepage_flags(t_size page_size)
{
	t_u32	flags;

	flags = -(page_size == HUGEPAGE_2MB) & xft_map_huge_2mb;
	flags |= -(page_size == HUGEPAGE_8MB) & xft_map_huge_8mb;
	flags |= -(page_size == HUGEPAGE_16MB) & xft_map_huge_16mb;
	flags |= -(page_size == HUGEPAGE_256MB) & xft_map_huge_256mb;
	flags |= -(page_size == HUGEPAGE_512MB) & xft_map_huge_512mb;
	flags |= -(page_size == HUGEPAGE_1GB) & xft_map_huge_1gb;
	flags |= -(page_size == HUGEPAGE_2GB) & xft_map_huge_2gb;
	flags |= -(page_size == HUGEPAGE_16GB) & xft_map_huge_16gb;
	return ((int)flags);
}

#endif
