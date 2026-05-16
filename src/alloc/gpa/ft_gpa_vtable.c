/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gpa_vtable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/16 23:46:48 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"

__attribute__((__nonnull__(1)))
static t_buffer	gpa_allocate(void *alloc, size_t size, size_t align)
{
	return (ft_gpa_alloc(alloc, size, align));
}

__attribute__((__nonnull__(1)))
static void	gpa_free(void *alloc, t_buffer old)
{
	ft_gpa_free(alloc, old);
}

__attribute__((__nonnull__(1)))
static t_buffer	gpa_reallocate(void *alloc, t_buffer old, size_t new_size,
				size_t align)
{
	return (ft_gpa_realloc(alloc, old, new_size, align));
}

__attribute__((__nonnull__(1)))
t_allocator	ft_gpa_allocator(t_gpa *gpa)
{
	return ((t_allocator){
		.interface = {
			.free = gpa_free,
			.realloc = gpa_reallocate,
			.allocate = gpa_allocate,
			.destroy = nullptr,
		},
		.allocator = gpa,
	});
}
