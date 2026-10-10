/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_report_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_gpa.h"

__attribute__((__nonnull__(1)))
t_buffer	xft_reporta_realloc(t_any alloc, t_buffer buf,
	t_size newsize, t_size align)
{
	t_reporta		*gpa;
	t_buffer		buf2;

	if (buf.mem == nullptr)
		__builtin_unreachable();
	gpa = (t_reporta *)alloc;
	if (newsize <= buf.size)
		return (buf);
	if (GPA_CLASSES <= 60 - xft_memclz_u64(buf.size))
		return (xft_palloc_resize(buf, newsize));
	buf2 = xft_reporta_alloc(gpa, newsize, align);
	if (!buf2.mem)
		return (xft_fatptr(nullptr, 0));
	xft_memcpy(buf2.mem, buf.mem, buf.size);
	xft_reporta_free(gpa, buf);
	return (buf2);
}
