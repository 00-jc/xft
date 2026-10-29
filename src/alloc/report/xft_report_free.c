/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_report_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_gpa.h>

__attribute__((__nonnull__(1)))
void	xft_reporta_free(t_any allocator, t_buffer buf)
{
	t_size		freelist;
	t_reporta	*gpa;

	if (buf.mem == nullptr)
		__builtin_unreachable();
	gpa = (t_reporta *)allocator;
	++gpa->n_frees;
	freelist = 60 - xft_memclz_u64(buf.size);
	if (GPA_CLASSES <= freelist)
	{
		xft_palloc_free(buf);
		return ;
	}
	++gpa->free_depth[freelist];
	*(t_any *)buf.mem = gpa->free[freelist];
	gpa->free[freelist] = buf.mem;
}

__attribute__((__nonnull__(1)))
void	xft_reporta_carve_tail(t_reporta *gpa)
{
	t_size	rem;
	t_size	chunk;
	t_size	freelist;

	rem = (t_uptr)gpa->slab + gpa->slabsize - (t_uptr)gpa->bmp;
	if (__builtin_expect(!rem || !xft_palloc_commit(gpa->bmp, rem), 0))
		return ;
	while (rem)
	{
		chunk = rem & -rem;
		freelist = 60 - xft_memclz_u64(chunk);
		++gpa->free_depth[freelist];
		*(t_any *)gpa->bmp = gpa->free[freelist];
		gpa->free[freelist] = gpa->bmp;
		gpa->bmp = (t_any)((t_blk8w)gpa->bmp + chunk);
		rem -= chunk;
	}
}
