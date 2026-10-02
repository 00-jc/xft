/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_report.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/09/02 22:58:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "primitives.h"
#include "math.h"
#include "io.h"
#include "fmt.h"

#define R1 "reporta (%x) report:\n  allocs:    %q\n  frees:     %q\n"
#define R2 "reuses:    %q\n  misses:    %q\n  paged:     %q\n  slabs:"
#define R3 "     %q\n  avg frag:  %f bytes\n  leaks:     %q\n  owned:"
#define R4 " %q bytes\n"

t_reporta	xft_reporta(void)
{
	t_reporta		gpa;
	t_buffer		buf;

	buf = xft_palloc(GPA_SLABSIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_reporta){0});
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
	gpa.slabs = 1;
	return (gpa);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline void	xft_reporta_report(t_reporta *gpa)
{
	const t_size	size = sizeof(R1 R2 R3 R4);
	t_size			args[10];
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
		xft_munmap((t_any)ptr, gpa->slabsize);
		ptr = next;
	}
}
