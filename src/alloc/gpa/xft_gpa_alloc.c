/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gpa_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/27 15:26:18 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_gpa.h"

__attribute__((__nonnull__(1), __always_inline__))
static inline int	xft_advance_slab(t_gpa *gpa)
{
	t_buffer	buf;
	t_any		*prev;

	buf = xft_palloc(GPA_SLABSIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return (0);
	prev = (t_any *)gpa->slab;
	gpa->slab = buf.mem;
	*(t_any *)gpa->slab = (t_any)prev;
	gpa->bmp = (t_blk8w)gpa->slab + sizeof(t_any *);
	return (1);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	xft_return_ptr(t_gpa *gpa, t_size snapped, t_size align)
{
	t_any	new_ptr;

	new_ptr = xft_align_fwd(gpa->bmp, align);
	if (__builtin_expect(
			(t_uptr)new_ptr + snapped
			>= (t_uptr)gpa->slab + gpa->slabsize
			&& !xft_advance_slab(gpa), 0))
		return (xft_fatptr(nullptr, 0));
	new_ptr = xft_align_fwd(gpa->bmp, align);
	gpa->bmp = (t_any)((t_blk8w)new_ptr + snapped);
	return (xft_fatptr(new_ptr, snapped));
}

__attribute__((__nonnull__(1)))
t_buffer	xft_gpa_alloc(t_any alloc, t_size size, t_size align)
{
	t_any	new_ptr;
	t_size	freelist;
	t_size	snapped;
	t_gpa	*gpa;

	gpa = (t_gpa *)alloc;
	snapped = xft_match_hugepage(size);
	snapped = xft_tern(snapped < align, xft_match_hugepage(align), snapped);
	freelist = 60 - xft_memclz_u64(snapped);
	if (GPA_CLASSES <= freelist)
	{
		new_ptr = xft_mmap(snapped, PROT_READ | PROT_WRITE,
				xft_match_hugepage_flags(snapped));
		new_ptr = (t_any)xft_tern(xft_map_failed(new_ptr),
				0, (t_uptr)new_ptr);
		return (xft_fatptr(new_ptr, snapped));
	}
	new_ptr = gpa->free[freelist];
	if (new_ptr)
	{
		gpa->free[freelist] = *(t_any *)new_ptr;
		return (xft_fatptr(new_ptr, snapped));
	}
	return (xft_return_ptr(gpa, snapped, align));
}
