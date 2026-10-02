/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gpa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_gpa.h"

t_gpa	xft_gpa(void)
{
	t_gpa		gpa;
	t_buffer	buf;

	buf = xft_palloc(GPA_SLABSIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_gpa){0});
	xft_memset((t_any)gpa.free, 0, sizeof(t_uptr) * GPA_CLASSES);
	gpa.slab = buf.mem;
	*(t_any *)gpa.slab = nullptr;
	gpa.bmp = (t_blk8w)gpa.slab + sizeof(t_any *);
	gpa.slabsize = buf.size;
	return (gpa);
}

__attribute__((__nonnull__(1)))
void	xft_gpa_destroy(t_gpa *gpa)
{
	t_any	*ptr;
	t_any	*next;

	ptr = gpa->slab;
	while (ptr != nullptr)
	{
		next = *ptr;
		xft_munmap(ptr, gpa->slabsize);
		ptr = next;
	}
}
