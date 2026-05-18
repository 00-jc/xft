/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_report.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:47:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 19:14:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"
#include "io.h"

t_reporta	ft_reporta(void)
{
	t_reporta		gpa;
	t_buffer		buf;

	buf = ft_palloc(GPA_SLABSIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_reporta){0});
	ft_memset((void *)gpa.free, 0, sizeof(t_uptr) * GPA_CLASSES);
	ft_memset((void *)gpa.free_depth, 0, sizeof(size_t) * GPA_CLASSES);
	gpa.slab = buf.mem;
	*(void **)gpa.slab = nullptr;
	gpa.bmp = (t_blk8w)gpa.slab + sizeof(void **);
	gpa.slabsize = buf.size;
	gpa.avg_frag = 0;
	gpa.n_allocs = 0;
	gpa.n_frees = 0;
	gpa.reuses = 0;
	gpa.slabs = 1;
	return (gpa);
}

__attribute__((__nonnull__(1), __always_inline__))
static inline void	ft_reporta_report(t_reporta *gpa)
{
	size_t	i;

	ft_fprintf(STDERR_FILENO,
		"reporta (%lx) report:\n"
		"  allocs:    %lu\n"
		"  frees:     %lu\n"
		"  reuses:    %lu\n"
		"  misses:    %lu\n"
		"  paged:     %lu\n"
		"  slabs:     %lu\n"
		"  avg frag:  %f bytes\n"
		"  leaks:     %lu\n"
		"  owned:     %lu bytes\n",
		gpa,
		gpa->n_allocs, gpa->n_frees, gpa->reuses,
		gpa->misses, gpa->paged, gpa->slabs,
		gpa->avg_frag, gpa->n_allocs - gpa->n_frees,
		gpa->slabsize * gpa->slabs);
	i = 0;
	while (i < GPA_CLASSES)
	{
		ft_fprintf(STDERR_FILENO,
			"  free[%lu]: %lu chained at exit\n", 1 << (i + 3), gpa->free_depth[i]);
		i++;
	}
}

__attribute__((__nonnull__(1)))
void	ft_reporta_destroy(t_reporta *gpa)
{
	void	**ptr;
	void	**next;

	ft_reporta_report(gpa);
	ptr = gpa->slab;
	while (ptr != nullptr)
	{
		next = *ptr;
		ft_munmap(ptr, gpa->slabsize);
		ptr = next;
	}
}
