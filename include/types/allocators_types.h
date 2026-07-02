/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocators_types.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/02 22:32:21 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATORS_TYPES_H
# define ALLOCATORS_TYPES_H

# include "primitives.h"

typedef void		(*t_free)(t_any alloc, t_buffer old)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_reallocate)(t_any alloc, t_buffer old, t_size new_size,\
						t_size align)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_allocate)(t_any alloc, t_size size, t_size align)\
						__attribute__((__nonnull__(1)));

typedef void		(*t_destroy)(t_any alloc)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_clone)(t_any self, t_buffer buffer)\
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
	t_any				allocator;
}	t_allocator;

#endif
