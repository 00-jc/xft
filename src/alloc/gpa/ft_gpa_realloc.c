/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpa_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 22:16:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/16 23:58:37 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"

__attribute__((__nonnull__(1)))
t_buffer	ft_gpa_realloc(void *alloc, t_buffer buf,
	size_t newsize, size_t align)
{
	t_gpa		*gpa;
	size_t		freelist[2];
	size_t		snapped;
	t_buffer	buf2;

	if (buf.mem == nullptr)
		__builtin_unreachable();
	gpa = (t_gpa *)alloc;
	snapped = ft_match_hugepage(newsize);
	snapped = ft_tern(snapped < align, ft_match_hugepage(align), snapped);
	freelist[0] = 60 - ft_memclz_u64(buf.size);
	freelist[1] = 60 - ft_memclz_u64(snapped);
	if (freelist[0] == freelist[1] || newsize <= buf.size)
		return (buf);
	if (GPA_CLASSES <= freelist[1])
		return (ft_palloc_resize(buf, newsize));
	buf2 = ft_gpa_alloc(gpa, newsize, align);
	if (!buf2.mem)
		return (ft_fatptr(nullptr, 0));
	ft_memcpy(buf2.mem, buf.mem, buf.size);
	ft_gpa_free(gpa, buf);
	return (buf2);
}
