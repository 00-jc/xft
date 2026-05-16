/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 22:47:10 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/16 22:13:12 by jaicastr         ###   ########.fr       */
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
	gpa.bmp = gpa.slab;
	gpa.slabsize = buf.size;
	return (gpa);
}
