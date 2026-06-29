/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_palloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 18:18:28 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/16 23:20:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_palloc.h"

__attribute__((__always_inline__))
inline t_buffer	ft_palloc(t_size size)
{
	t_size	snapped;
	void	*mem;
	int		flags;

	snapped = ft_match_hugepage(size);
	flags = ft_match_hugepage_flags(snapped);
	mem = ft_mmap(snapped, 0, flags);
	return ((t_buffer){
		.size = snapped,
		.mem = (void *)ft_tern(mem != (void *)MAP_FAILED, (t_u64a)mem, 0),
	});
}

__attribute__((__always_inline__))
inline t_buffer	ft_palloc_resize(t_buffer b, t_size new_size)
{
	t_size		snapped;
	int			flags;
	void		*mem;
	t_buffer	new_b;

	snapped = ft_match_hugepage(new_size);
	if (snapped == b.size)
	{
		mem = ft_mremap(b.size, snapped, b.mem, 0);
		return ((t_buffer){
			.size = snapped,
			.mem = (void *)ft_tern(mem != (void *)MAP_FAILED, (t_u64a)mem, 0)});
	}
	flags = ft_match_hugepage_flags(snapped);
	mem = ft_mmap(snapped, 0, flags);
	new_b = (t_buffer){
		.size = snapped,
		.mem = (void *)ft_tern(mem != (void *)MAP_FAILED, (t_u64a)mem, 0),
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
