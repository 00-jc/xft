/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_huge_matcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_hugepage.h"

__attribute__((const))
t_size	ft_match_hugepage(t_size requested_size)
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
	page_size = ft_tern(requested_size <= 1048576,
			ft_next_pow2(requested_size), page_size);
	return (ft_tern(page_size < 8, 8, page_size));
}

__attribute__((const))
int	ft_match_hugepage_flags(t_size page_size)
{
	t_u32	flags;

	flags = -(page_size == HUGEPAGE_2MB) & MAP_HUGE_2MB;
	flags |= -(page_size == HUGEPAGE_8MB) & MAP_HUGE_8MB;
	flags |= -(page_size == HUGEPAGE_16MB) & MAP_HUGE_16MB;
	flags |= -(page_size == HUGEPAGE_256MB) & MAP_HUGE_256MB;
	flags |= -(page_size == HUGEPAGE_512MB) & MAP_HUGE_512MB;
	flags |= -(page_size == HUGEPAGE_1GB) & MAP_HUGE_1GB;
	flags |= -(page_size == HUGEPAGE_2GB) & MAP_HUGE_2GB;
	flags |= -(page_size == HUGEPAGE_16GB) & MAP_HUGE_16GB;
	return ((int)flags);
}
