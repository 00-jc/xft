/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena_vtable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/16 23:58:15 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alloc.h"
#include "mem.h"

__attribute__((__nonnull__(1)))
static t_buffer	arena_allocate(void *alloc, size_t size, size_t align)
{
	void	*ptr;

	ptr = ft_arena_alloc((t_arena *)alloc, size, align);
	return (ft_fatptr(ptr, size));
}

__attribute__((__nonnull__(1)))
static void	arena_free(void *alloc, t_buffer old)
{
	(void)alloc;
	(void)old;
}

__attribute__((__nonnull__(1)))
static t_buffer	arena_reallocate(void *alloc, t_buffer old, size_t new_size,
					size_t align)
{
	void	*ptr;
	size_t	copy_size;

	ptr = ft_arena_alloc((t_arena *)alloc, new_size, align);
	if (!ptr)
		return ((t_buffer){0});
	copy_size = ft_tern(old.size < new_size, old.size, new_size);
	ft_memcpy(ptr, old.mem, copy_size);
	return (ft_fatptr(ptr, new_size));
}

__attribute__((__nonnull__(1)))
static void	arena_destroy(void *alloc)
{
	ft_destroy_arena((t_arena *)alloc);
}

__attribute__((__nonnull__(1)))
t_allocator	ft_arena_allocator(t_arena *arena)
{
	return ((t_allocator){
		.interface = {
			.free = arena_free,
			.realloc = arena_reallocate,
			.allocate = arena_allocate,
			.destroy = arena_destroy,
		},
		.allocator = arena,
	});
}
