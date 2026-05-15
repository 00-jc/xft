/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_palloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:18:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 19:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_hugepage.h"

__attribute__((__always_inline__))
inline t_buffer	ft_palloc(size_t size)
{
	t_buffer	b;
	size_t		snapped;
	int			flags;

	snapped = ft_match_hugepage(size);
	flags = ft_match_hugepage_flags(snapped);
	b = (t_buffer){
		.size = snapped,
		.mem = ft_mmap(snapped, 0, flags),
	};
	return (b);
}

__attribute__((__always_inline__))
inline t_buffer	ft_palloc_resize(t_buffer b, size_t new_size)
{
	size_t		snapped;
	int			flags;
	t_buffer	new_b;

	snapped = ft_match_hugepage(new_size);
	if (snapped == b.size)
	{
		return ((t_buffer){
			.size = snapped,
			.mem = ft_mremap(b.size, snapped, b.mem, 0)});
	}
	flags = ft_match_hugepage_flags(snapped);
	new_b = (t_buffer){
		.size = snapped,
		.mem = ft_mmap(snapped, 0, flags),
	};
	ft_memcpy(new_b.mem, b.mem, b.size);
	ft_munmap(b.mem, b.size);
	return (new_b);
}

__attribute__((__always_inline__))
inline void	ft_palloc_free(t_buffer b)
{
	ft_munmap(b.mem, b.size);
}
