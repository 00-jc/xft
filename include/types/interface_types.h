/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERFACE_TYPES_H
# define INTERFACE_TYPES_H

# include "primitives.h"

typedef void		(*t_free)(void *alloc, t_buffer old)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_reallocate)(void *alloc, t_buffer old, size_t new_size,\
						size_t align)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_allocate)(void *alloc, size_t size, size_t align)\
						__attribute__((__nonnull__(1)));

typedef void		(*t_destroy)(void *alloc)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_clone)(void *self, t_buffer buffer)\
						__attribute__((__nonnull__(1)));

typedef struct e_alloc_interface
{
	t_free			free;
	t_reallocate	realloc;
	t_allocate		allocate;
	t_destroy		destroy;
	t_clone			clone;
}	t_alloc_interface;

typedef struct s_allocator
{
	t_alloc_interface	interface;
	void				*allocator;
}	t_allocator;

#endif
