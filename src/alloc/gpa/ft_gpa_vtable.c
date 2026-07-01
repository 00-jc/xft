/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpa_vtable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"

__attribute__((__nonnull__(1)))
static void	gpa_destroy(void *alloc)
{
	ft_gpa_destroy((t_gpa *)alloc);
}

__attribute__((__nonnull__(1)))
static t_buffer	gpa_allocate(void *alloc, t_size size, t_size align)
{
	return (ft_gpa_alloc(alloc, size, align));
}

__attribute__((__nonnull__(1)))
static void	gpa_free(void *alloc, t_buffer old)
{
	ft_gpa_free(alloc, old);
}

__attribute__((__nonnull__(1)))
static t_buffer	gpa_reallocate(void *alloc, t_buffer old, t_size new_size,
				t_size align)
{
	return (ft_gpa_realloc(alloc, old, new_size, align));
}

__attribute__((__nonnull__(1), __const__))
t_allocator	ft_gpa_allocator(t_gpa *gpa)
{
	return ((t_allocator){
		.interface = {
			.free = gpa_free,
			.realloc = gpa_reallocate,
			.allocate = gpa_allocate,
			.destroy = gpa_destroy,
			.clone = ft_alloc_clone,
		},
		.allocator = gpa,
	});
}
