/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_palloc_vtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xft_p_palloc.h"

__attribute__((__nonnull__(1)))
static t_buffer	palloc_allocate(t_any alloc, t_size size, t_size align)
{
	(void)alloc;
	(void)align;
	return (xft_palloc(size));
}

__attribute__((__nonnull__(1)))
static t_buffer	palloc_reallocate(t_any alloc, t_buffer old, t_size new_size,
					t_size align)
{
	(void)alloc;
	(void)align;
	return (xft_palloc_resize(old, new_size));
}

__attribute__((__nonnull__(1)))
static void	palloc_free(t_any alloc, t_buffer old)
{
	(void)alloc;
	xft_palloc_free(old);
}

__attribute__((__const__))
t_allocator	xft_new_page_alloc(void)
{
	static t_page_alloc	instance = {0};

	return ((t_allocator){
		.vtable = {
			.free = palloc_free,
			.realloc = palloc_reallocate,
			.allocate = palloc_allocate,
			.destroy = nullptr,
			.clone = xft_alloc_clone,
		},
		.allocator = &instance,
	});
}
