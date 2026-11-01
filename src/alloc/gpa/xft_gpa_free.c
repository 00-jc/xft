/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gpa_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/xft_p_gpa.h>

__attribute__((__nonnull__(1)))
void	xft_gpa_free(t_any allocator, t_buffer buf)
{
	t_size	freelist;
	t_gpa	*gpa;

	if (buf.mem == nullptr)
		__builtin_unreachable();
	gpa = (t_gpa *)allocator;
	freelist = 61 - xft_memclz_u64(buf.size - 1);
	if (GPA_SLABSIZE <= buf.size)
	{
		if (GPA_FREELISTS <= freelist || GPA_BIGPAGES <= gpa->bigpages)
		{
			xft_palloc_free(buf);
			return ;
		}
		++gpa->bigpages;
		xft_palloc_discard(buf.mem, buf.size);
	}
	*(t_any *)buf.mem = gpa->free[freelist];
	gpa->free[freelist] = buf.mem;
}
