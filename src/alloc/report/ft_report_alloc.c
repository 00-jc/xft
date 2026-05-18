/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_report_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 01:40:30 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 16:31:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"

__attribute__((__nonnull__(1), __always_inline__))
static inline int	ft_advance_slab(t_reporta *gpa)
{
	t_buffer	buf;
	void		**prev;

	buf = ft_palloc(GPA_SLABSIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return (0);
	prev = gpa->slab;
	++gpa->slabs;
	gpa->slab = buf.mem;
	*(void **)gpa->slab = prev;
	gpa->bmp = (t_blk8w)gpa->slab + sizeof(void **);
	return (1);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	ft_return_ptr(t_reporta *gpa,
	size_t sizes[2], size_t align)
{
	void	*new_ptr;

	++gpa->misses;
	new_ptr = ft_align_fwd(gpa->bmp, align - 1);
	if (__builtin_expect(
			(t_uptr)new_ptr + sizes[1]
			>= (t_uptr)gpa->slab + gpa->slabsize
			&& !ft_advance_slab(gpa), 0))
		return (ft_fatptr(nullptr, 0));
	new_ptr = ft_align_fwd(gpa->bmp, align - 1);
	gpa->avg_frag += (t_f64)((t_f64)((sizes[1] - sizes[0])
				+ (t_uptr)new_ptr - (t_uptr)gpa->bmp)
			- gpa->avg_frag) / (t_f64)gpa->n_allocs;
	gpa->bmp = (void *)((t_blk8w)new_ptr + sizes[1]);
	return (ft_fatptr(new_ptr, sizes[1]));
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	ft_reuse_ptr(t_reporta *gpa, size_t freelist,
	void *new_ptr, size_t sizes[2])
{
	++gpa->reuses;
	--gpa->free_depth[freelist];
	gpa->avg_frag += (t_f64)((t_f64)(sizes[1] - sizes[0]) - gpa->avg_frag)
		/ (t_f64)gpa->n_allocs;
	gpa->free[freelist] = *(void **)new_ptr;
	return (ft_fatptr(new_ptr, sizes[1]));
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	ft_paged_ptr(t_reporta *gpa, size_t sizes[2])
{
	void	*new_ptr;

	++gpa->paged;
	new_ptr = ft_mmap(sizes[1], 0, ft_match_hugepage_flags(sizes[1]));
	if (__builtin_expect(new_ptr == MAP_FAILED, 0))
		return (ft_fatptr(nullptr, 0));
	gpa->avg_frag += (t_f64)((t_f64)(sizes[1] - sizes[0]) - gpa->avg_frag)
		/ (t_f64)gpa->n_allocs;
	return (ft_fatptr(new_ptr, sizes[1]));
}

__attribute__((__nonnull__(1)))
t_buffer	ft_reporta_alloc(void *alloc, size_t size, size_t align)
{
	void		*new_ptr;
	size_t		freelist;
	size_t		snapped;
	t_reporta	*gpa;

	gpa = (t_reporta *)alloc;
	snapped = ft_match_hugepage(size);
	snapped = ft_tern(snapped < align, ft_match_hugepage(align), snapped);
	freelist = 60 - ft_memclz_u64(snapped);
	++gpa->n_allocs;
	if (GPA_CLASSES <= freelist)
		return (ft_paged_ptr(gpa, (size_t[2]){snapped, size}));
	new_ptr = gpa->free[freelist];
	if (new_ptr)
		return (ft_reuse_ptr(gpa, freelist, new_ptr,
				(size_t[2]){size, snapped}));
	return (ft_return_ptr(gpa, (size_t[2]){size, snapped}, align));
}
