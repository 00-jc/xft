/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_huge_matcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 22:24:25 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_hugepage.h"

__attribute__((const))
static inline size_t	ft_snap_tiny(size_t size)
{
	size_t	s;

	s = (-(size <= 1024) & 1024) | (-(size > 1024) & size);
	s = (-(size <= 512) & 512) | (-(size > 512) & s);
	s = (-(size <= 256) & 256) | (-(size > 256) & s);
	s = (-(size <= 128) & 128) | (-(size > 128) & s);
	s = (-(size <= 64) & 64) | (-(size > 64) & s);
	s = (-(size <= 32) & 32) | (-(size > 32) & s);
	s = (-(size <= 16) & 16) | (-(size > 16) & s);
	return (ft_tern(s < 8, 8, s));
}

__attribute__((const))
static inline size_t	ft_snap_small(size_t size)
{
	size_t	s;

	s = (-(size <= 65536) & 65536) | (-(size > 65536) & size);
	s = (-(size <= 32768) & 32768) | (-(size > 32768) & s);
	s = (-(size <= 16384) & 16384) | (-(size > 16384) & s);
	s = (-(size <= 8192) & 8192) | (-(size > 8192) & s);
	s = (-(size <= 4096) & 4096) | (-(size > 4096) & s);
	s = (-(size <= 2048) & 2048) | (-(size > 2048) & s);
	return (s);
}

__attribute__((const))
static inline size_t	ft_snap_medium(size_t size)
{
	size_t	s;

	s = (-(size <= 1048576) & 1048576) | (-(size > 1048576) & size);
	s = (-(size <= 524288) & 524288) | (-(size > 524288) & s);
	s = (-(size <= 262144) & 262144) | (-(size > 262144) & s);
	s = (-(size <= 131072) & 131072) | (-(size > 131072) & s);
	return (s);
}

__attribute__((const))
size_t	ft_match_hugepage(size_t requested_size)
{
	size_t	page_size;

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
			ft_snap_medium(requested_size), page_size);
	page_size = ft_tern(requested_size <= 65536,
			ft_snap_small(requested_size), page_size);
	page_size = ft_tern(requested_size <= 1024,
			ft_snap_tiny(requested_size), page_size);
	return (page_size);
}

__attribute__((const))
int	ft_match_hugepage_flags(size_t page_size)
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
