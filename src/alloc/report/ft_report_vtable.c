/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_report_vtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 15:41:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_gpa.h"

__attribute__((__nonnull__(1)))
static void	gpa_destroy(void *alloc)
{
	ft_reporta_destroy((t_reporta *)alloc);
}

__attribute__((__nonnull__(1)))
static t_buffer	gpa_allocate(void *alloc, size_t size, size_t align)
{
	return (ft_reporta_alloc(alloc, size, align));
}

__attribute__((__nonnull__(1)))
static void	gpa_free(void *alloc, t_buffer old)
{
	ft_reporta_free(alloc, old);
}

__attribute__((__nonnull__(1)))
static t_buffer	gpa_reallocate(void *alloc, t_buffer old, size_t new_size,
				size_t align)
{
	return (ft_reporta_realloc(alloc, old, new_size, align));
}

__attribute__((__nonnull__(1), __const__))
t_allocator	ft_reporta_allocator(t_reporta *gpa)
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
