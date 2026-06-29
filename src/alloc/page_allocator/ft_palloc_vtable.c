/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_palloc_vtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/16 23:47:49 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private/ft_p_palloc.h"

__attribute__((__nonnull__(1)))
static t_buffer	palloc_allocate(void *alloc, t_size size, t_size align)
{
	(void)alloc;
	(void)align;
	return (ft_palloc(size));
}

__attribute__((__nonnull__(1)))
static t_buffer	palloc_reallocate(void *alloc, t_buffer old, t_size new_size,
					t_size align)
{
	(void)alloc;
	(void)align;
	return (ft_palloc_resize(old, new_size));
}

__attribute__((__nonnull__(1)))
static void	palloc_free(void *alloc, t_buffer old)
{
	(void)alloc;
	ft_palloc_free(old);
}

__attribute__((__const__))
t_allocator	ft_new_page_alloc(void)
{
	static t_page_alloc	instance = {0};

	return ((t_allocator){
		.interface = {
			.free = palloc_free,
			.realloc = palloc_reallocate,
			.allocate = palloc_allocate,
			.destroy = nullptr,
			.clone = ft_alloc_clone,
		},
		.allocator = &instance,
	});
}
