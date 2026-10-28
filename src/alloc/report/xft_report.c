/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_report.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/02 22:58:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/alloc.h>
#include <xft/primitives.h>
#include <xft/math.h>
#include <xft/io.h>
#include <xft/fmt.h>

#define R1 "reporta (%x) report:\n  allocs:    %q\n  frees:     %q\n"
#define R2 "  reuses:    %q\n  misses:    %q\n  paged:     %q\n"
#define R3 "  slabs:     %q\n  avg frag:  %f bytes\n  leaks:     %q\n"
#define R4 "  owned:     %q bytes\n"

t_reporta	xft_new_reporta(void)
{
	t_reporta		gpa;
	t_buffer		buf;

	buf = xft_palloc_reserve(GPA_SLABSIZE);
	if (__builtin_expect(!buf.mem, 0))
		return ((t_reporta){0});
	if (__builtin_expect(!xft_palloc_commit(buf.mem, sizeof(t_any *)), 0))
		return (xft_palloc_free(buf), (t_reporta){0});
	xft_memset((t_any)gpa.free, 0, sizeof(t_uptr) * GPA_CLASSES);
	xft_memset((t_any)gpa.free_depth, 0, sizeof(t_size) * GPA_CLASSES);
	gpa.slab = buf.mem;
	*(t_any *)gpa.slab = nullptr;
	gpa.bmp = (t_blk8w)gpa.slab + sizeof(t_any *);
	gpa.slabsize = buf.size;
	gpa.avg_frag = 0;
	gpa.n_allocs = 0;
	gpa.n_frees = 0;
	gpa.reuses = 0;
	gpa.misses = 0;
	gpa.paged = 0;
	gpa.slabs = 1;
	return (gpa);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline void	xft_reporta_report(t_reporta *gpa)
{
	const t_size	size = sizeof(R1 R2 R3 R4) - 1;
	t_u64			args[10];
	t_writer		writer;

	writer = xft_get_fs_writer(xft_fatptr(gpa->buffer, REPORTA_BUFFER),
			xft_get_stderr());
	args[0] = (t_uptr)gpa;
	args[1] = gpa->n_allocs;
	args[2] = gpa->n_frees;
	args[3] = gpa->reuses;
	args[4] = gpa->misses;
	args[5] = gpa->paged;
	args[6] = gpa->slabs;
	args[7] = (t_dp){.f = gpa->avg_frag}.i;
	args[8] = gpa->n_allocs - gpa->n_frees;
	args[9] = gpa->slabsize * gpa->slabs;
	xft_fmt_writer(&writer, xft_fatptr((t_u8 *)R1 R2 R3 R4, size), args);
	xft_writer_flush(&writer);
}

__attribute__((__nonnull__(1)))
void	xft_reporta_destroy(t_reporta *gpa)
{
	t_any	*ptr;
	t_any	*next;

	xft_reporta_report(gpa);
	ptr = (t_any *)gpa->slab;
	while (ptr != nullptr)
	{
		next = (t_any *)*ptr;
		xft_palloc_free(xft_fatptr((t_any)ptr, gpa->slabsize));
		ptr = next;
	}
}
