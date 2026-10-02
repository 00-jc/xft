/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_palloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/03 21:37:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_palloc.h"

__attribute__((__always_inline__, __used__))
inline t_buffer	xft_palloc(t_size size)
{
	t_size	snapped;
	t_any	mem;
	int		flags;

	snapped = xft_match_hugepage(size);
	flags = xft_match_hugepage_flags(snapped);
	mem = xft_mmap(snapped, PROT_READ | PROT_WRITE, flags);
	return ((t_buffer){
		.size = snapped,
		.mem = (t_any)xft_tern(!xft_map_failed(mem), (t_u64a)mem, 0),
	});
}

__attribute__((__always_inline__, __used__))
inline t_buffer	xft_palloc_resize(t_buffer b, t_size new_size)
{
	t_size		snapped;
	int			flags;
	t_any		mem;
	t_buffer	new_b;

	snapped = xft_match_hugepage(new_size);
	if (__builtin_expect(snapped == b.size, 1))
		return (b);
	flags = xft_match_hugepage_flags(snapped);
	mem = xft_mmap(snapped, PROT_READ | PROT_WRITE, flags);
	new_b = (t_buffer){
		.size = snapped,
		.mem = (t_any)xft_tern(!xft_map_failed(mem), (t_u64a)mem, 0),
	};
	xft_memcpy(new_b.mem, b.mem, b.size);
	xft_munmap(b.mem, b.size);
	return (new_b);
}

__attribute__((__always_inline__, __used__))
inline void	xft_palloc_free(t_buffer b)
{
	xft_munmap(b.mem, b.size);
}
