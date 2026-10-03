/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_arena_vtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "mem.h"

__attribute__((__nonnull__(1)))
static t_buffer	arena_allocate(t_any alloc, t_size size, t_size align)
{
	t_any	ptr;

	ptr = xft_arena_alloc((t_arena *)alloc, size, align);
	return (xft_fatptr(ptr, size));
}

__attribute__((__nonnull__(1)))
static void	arena_free(t_any alloc, t_buffer old)
{
	(void)alloc;
	(void)old;
}

__attribute__((__nonnull__(1)))
static t_buffer	arena_reallocate(t_any alloc, t_buffer old, t_size new_size,
					t_size align)
{
	t_any	ptr;
	t_size	copy_size;

	ptr = xft_arena_alloc((t_arena *)alloc, new_size, align);
	if (!ptr)
		return ((t_buffer){0});
	copy_size = xft_tern(old.size < new_size, old.size, new_size);
	xft_memcpy(ptr, old.mem, copy_size);
	return (xft_fatptr(ptr, new_size));
}

__attribute__((__nonnull__(1)))
static void	arena_destroy(t_any alloc)
{
	xft_destroy_arena((t_arena *)alloc);
}

__attribute__((__nonnull__(1), __const__))
t_allocator	xft_arena_allocator(t_arena *arena)
{
	return ((t_allocator){
		.vtable = {
			.free = arena_free,
			.realloc = arena_reallocate,
			.allocate = arena_allocate,
			.destroy = arena_destroy,
			.clone = xft_alloc_clone,
		},
		.allocator = arena,
	});
}
