/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_report_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_gpa.h"

__attribute__((__nonnull__(1), __always_inline__))
static inline int	xft_advance_slab(t_reporta *gpa)
{
	t_buffer	buf;
	t_any		*prev;

	buf = xft_fatptr(xft_mmap(GPA_SLABSIZE, PROT_READ | PROT_WRITE, 0),
			GPA_SLABSIZE);
	if (__builtin_expect(xft_map_failed(buf.mem), 0))
		return (0);
	if (__builtin_expect(!xft_mmap_commit(buf.mem, sizeof(t_any *),
				PROT_READ | PROT_WRITE, 0), 0))
		return (xft_munmap(buf.mem, buf.size), 0);
	prev = gpa->slab;
	++gpa->slabs;
	gpa->slab = buf.mem;
	*(t_any *)gpa->slab = prev;
	gpa->bmp = (t_blk8w)gpa->slab + sizeof(t_any *);
	return (1);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	xft_return_ptr(t_reporta *gpa,
	t_size sizes[2], t_size align)
{
	t_any	new_ptr;

	++gpa->misses;
	new_ptr = xft_align_fwd(gpa->bmp, align);
	if (__builtin_expect(
			(t_uptr)new_ptr + sizes[1]
			>= (t_uptr)gpa->slab + gpa->slabsize
			&& !xft_advance_slab(gpa), 0))
		return (xft_fatptr(nullptr, 0));
	new_ptr = xft_align_fwd(gpa->bmp, align);
	if (__builtin_expect(!xft_mmap_commit(new_ptr, sizes[1],
				PROT_READ | PROT_WRITE, 0), 0))
		return (xft_fatptr(nullptr, 0));
	gpa->avg_frag += (t_f64)((t_f64)((sizes[1] - sizes[0])
				+ (t_uptr)new_ptr - (t_uptr)gpa->bmp)
			- gpa->avg_frag) / (t_f64)gpa->n_allocs;
	gpa->bmp = (t_any)((t_blk8w)new_ptr + sizes[1]);
	return (xft_fatptr(new_ptr, sizes[1]));
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	xft_reuse_ptr(t_reporta *gpa, t_size freelist,
	t_any new_ptr, t_size sizes[2])
{
	++gpa->reuses;
	--gpa->free_depth[freelist];
	gpa->avg_frag += (t_f64)((t_f64)(sizes[1] - sizes[0]) - gpa->avg_frag)
		/ (t_f64)gpa->n_allocs;
	gpa->free[freelist] = *(t_any *)new_ptr;
	return (xft_fatptr(new_ptr, sizes[1]));
}

__attribute__((__nonnull__(1), __always_inline__))
static inline t_buffer	xft_paged_ptr(t_reporta *gpa, t_size sizes[2])
{
	t_any	new_ptr;

	++gpa->paged;
	new_ptr = xft_mmap(sizes[1], PROT_READ | PROT_WRITE,
			xft_match_hugepage_flags(sizes[1]));
	if (__builtin_expect(xft_map_failed(new_ptr), 0))
		return (xft_fatptr(nullptr, 0));
	if (__builtin_expect(!xft_mmap_commit(new_ptr, sizes[1],
				PROT_READ | PROT_WRITE, 0), 0))
		return (xft_munmap(new_ptr, sizes[1]), xft_fatptr(nullptr, 0));
	gpa->avg_frag += (t_f64)((t_f64)(sizes[1] - sizes[0]) - gpa->avg_frag)
		/ (t_f64)gpa->n_allocs;
	return (xft_fatptr(new_ptr, sizes[1]));
}

__attribute__((__nonnull__(1)))
t_buffer	xft_reporta_alloc(t_any alloc, t_size size, t_size align)
{
	t_any		new_ptr;
	t_size		freelist;
	t_size		snapped;
	t_reporta	*gpa;

	gpa = (t_reporta *)alloc;
	size = xft_tern(size < 8, 8, size);
	snapped = xft_next_pow2(size);
	snapped = xft_tern(snapped < align, xft_next_pow2(align), snapped);
	freelist = 60 - xft_memclz_u64(snapped);
	++gpa->n_allocs;
	if (GPA_CLASSES <= freelist)
		return (xft_paged_ptr(gpa, (t_size[2]){size,
				xft_match_hugepage(xft_tern(size < align, align, size))}));
	new_ptr = gpa->free[freelist];
	if (new_ptr)
		return (xft_reuse_ptr(gpa, freelist, new_ptr,
				(t_size[2]){size, snapped}));
	return (xft_return_ptr(gpa, (t_size[2]){size, snapped}, align));
}
