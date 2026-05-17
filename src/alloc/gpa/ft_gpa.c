/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:47:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 02:00:23 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"

t_gpa	ft_gpa(void)
{
	t_gpa		gpa;
	t_buffer	buf;

	buf = ft_palloc(GPA_SLABSIZE);
	if (__builtin_expect(buf.mem == nullptr, 0))
		return ((t_gpa){0});
	ft_memset((void *)gpa.free, 0, sizeof(t_uptr) * GPA_CLASSES);
	gpa.slab = buf.mem;
	*(void **)gpa.slab = nullptr;
	gpa.bmp = (t_blk8w)gpa.slab + sizeof(void **);
	gpa.slabsize = buf.size;
	return (gpa);
}

__attribute__((__nonnull__(1)))
void	ft_gpa_destroy(t_gpa *gpa)
{
	void	**ptr;
	void	**next;

	ptr = gpa->slab;
	while (ptr != nullptr)
	{
		next = *ptr;
		ft_munmap(ptr, gpa->slabsize);
		ptr = next;
	}
}
