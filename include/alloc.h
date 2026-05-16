/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/17 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "alloc/page_alloc.h"
# include "alloc/arena_alloc.h"

// VTABLE

typedef void		(*t_free)(void *alloc, t_buffer old)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_reallocate)(void *alloc, t_buffer old, size_t new_size,\
						size_t align)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_allocate)(void *alloc, size_t size, size_t align)\
						__attribute__((__nonnull__(1)));

typedef void		(*t_destroy)(void *alloc)\
						__attribute__((__nonnull__(1)));

typedef struct e_alloc_interface
{
	t_free			free;
	t_reallocate	realloc;
	t_allocate		allocate;
	t_destroy		destroy;
}	t_alloc_interface;

typedef struct s_allocator
{
	t_alloc_interface	interface;
	void				*allocator;
}	t_allocator;

// GPA

# define GPA_CLASSES 16ULL

typedef struct s_gpa
{
	void	*slab;
	size_t	slabsize;
	void	*bmp;
	void	*free[GPA_CLASSES];
}	t_gpa;

t_gpa		ft_gpa(void);
t_buffer	ft_gpa_alloc(void *alloc, size_t size, size_t align);
t_buffer	ft_gpa_realloc(void *alloc, t_buffer buf, size_t newsize,
				size_t align);
void		ft_gpa_free(void *allocator, t_buffer buf);

t_allocator	ft_arena_allocator(t_arena *arena);
t_allocator	ft_gpa_allocator(t_gpa *gpa);
t_allocator	ft_new_page_alloc(void);

#endif
