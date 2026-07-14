/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_palloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/03 21:37:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_palloc.h"

__attribute__((__always_inline__))
inline t_buffer	ft_palloc(t_size size)
{
	t_size	snapped;
	t_any	mem;
	int		flags;

	snapped = ft_match_hugepage(size);
	flags = ft_match_hugepage_flags(snapped);
	mem = ft_mmap(snapped, PROT_READ | PROT_WRITE, flags);
	return ((t_buffer){
		.size = snapped,
		.mem = (t_any)ft_tern(mem != (t_any)MAP_FAILED, (t_u64a)mem, 0),
	});
}

__attribute__((__always_inline__))
inline t_buffer	ft_palloc_resize(t_buffer b, t_size new_size)
{
	t_size		snapped;
	int			flags;
	t_any		mem;
	t_buffer	new_b;

	snapped = ft_match_hugepage(new_size);
	if (__builtin_expect(snapped == b.size, 1))
		return (b);
	flags = ft_match_hugepage_flags(snapped);
	mem = ft_mmap(snapped, PROT_READ | PROT_WRITE, flags);
	new_b = (t_buffer){
		.size = snapped,
		.mem = (t_any)ft_tern(mem != (t_any)MAP_FAILED, (t_u64a)mem, 0),
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
