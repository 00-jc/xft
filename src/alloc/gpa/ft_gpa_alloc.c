/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpa_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 01:40:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 02:44:28 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"

__attribute__((__nonnull__(1), __always_inline__))
static inline int	ft_advance_slab(t_gpa *gpa)
{
	t_buffer	buf;
	void		**prev;

	buf = ft_palloc(GPA_SLABSIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return (0);
	prev = gpa->slab;
	gpa->slab = buf.mem;
	*(void **)gpa->slab = prev;
	gpa->bmp = (t_blk8w)gpa->slab + sizeof(void **);
	return (1);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	ft_return_ptr(t_gpa *gpa, size_t snapped, size_t align)
{
	void	*new_ptr;

	new_ptr = ft_align_fwd(gpa->bmp, align - 1);
	if (__builtin_expect(
			(t_uptr)new_ptr + snapped
			>= (t_uptr)gpa->slab + gpa->slabsize
			&& !ft_advance_slab(gpa), 0))
		return (ft_fatptr(nullptr, 0));
	new_ptr = ft_align_fwd(gpa->bmp, align - 1);
	gpa->bmp = (void *)((t_blk8w)new_ptr + snapped);
	return (ft_fatptr(new_ptr, snapped));
}

__attribute__((__nonnull__(1)))
t_buffer	ft_gpa_alloc(void *alloc, size_t size, size_t align)
{
	void	*new_ptr;
	size_t	freelist;
	size_t	snapped;
	t_gpa	*gpa;

	gpa = (t_gpa *)alloc;
	snapped = ft_match_hugepage(size);
	snapped = ft_tern(snapped < align, ft_match_hugepage(align), snapped);
	freelist = 60 - ft_memclz_u64(snapped);
	if (GPA_CLASSES <= freelist)
	{
		new_ptr = ft_mmap(snapped, 0, ft_match_hugepage_flags(snapped));
		return (ft_fatptr(new_ptr, snapped));
	}
	new_ptr = gpa->free[freelist];
	if (new_ptr)
	{
		gpa->free[freelist] = *(void **)new_ptr;
		ft_memset(new_ptr, 0, snapped);
		return (ft_fatptr(new_ptr, snapped));
	}
	return (ft_return_ptr(gpa, snapped, align));
}
