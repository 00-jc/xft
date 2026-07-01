/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpa_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"

__attribute__((__nonnull__(1)))
void	ft_gpa_free(void *allocator, t_buffer buf)
{
	t_size	freelist;
	t_gpa	*gpa;

	if (buf.mem == nullptr)
		__builtin_unreachable();
	gpa = (t_gpa *)allocator;
	freelist = 60 - ft_memclz_u64(buf.size);
	if (GPA_CLASSES <= freelist)
	{
		ft_munmap(buf.mem, buf.size);
		return ;
	}
	*(void **)buf.mem = gpa->free[freelist];
	gpa->free[freelist] = buf.mem;
}
