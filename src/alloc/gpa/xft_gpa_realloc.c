/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_gpa_realloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/10 22:20:31 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_gpa.h"

__attribute__((__nonnull__(1)))
t_buffer	xft_gpa_realloc(t_any alloc, t_buffer buf,
	t_size newsize, t_size align)
{
	t_gpa		*gpa;
	t_buffer	buf2;

	if (buf.mem == nullptr)
		__builtin_unreachable();
	gpa = (t_gpa *)alloc;
	if (newsize <= buf.size && !((t_uptr)buf.mem & (align - 1)))
		return (buf);
	if (GPA_CLASSES <= 60 - xft_memclz_u64(buf.size))
		return (xft_palloc_resize(buf, newsize));
	buf2 = xft_gpa_alloc(gpa, newsize, align);
	if (__builtin_expect(!buf2.mem, 0))
		return (xft_fatptr(nullptr, 0));
	xft_memcpy(buf2.mem, buf.mem, buf.size);
	xft_gpa_free(gpa, buf);
	return (buf2);
}
