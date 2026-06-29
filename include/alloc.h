/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/18 19:43:54 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "alloc/page_alloc.h"
# include "alloc/arena_alloc.h"

// VTABLE

typedef void		(*t_free)(void *alloc, t_buffer old)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_reallocate)(void *alloc, t_buffer old, t_size new_size,\
						t_size align)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_allocate)(void *alloc, t_size size, t_size align)\
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

// GPA

# define GPA_CLASSES 	14ULL
# define GPA_SLABSIZE	131072ULL

typedef struct s_gpa
{
	void	*slab;
	t_size	slabsize;
	void	*bmp;
	void	*free[GPA_CLASSES];
}	t_gpa;

typedef struct s_reporta
{
	void	*slab;
	t_size	slabsize;
	void	*bmp;
	void	*free[GPA_CLASSES];
	t_size	n_allocs;
	t_size	n_frees;
	t_size	slabs;
	t_size	reuses;
	t_size	misses;
	t_size	free_depth[GPA_CLASSES];
	t_size	paged;
	t_f64	avg_frag;
}	t_reporta;

t_gpa		ft_gpa(void);
void		ft_gpa_destroy(t_gpa *gpa);
t_buffer	ft_gpa_alloc(void *alloc, t_size size, t_size align);
t_buffer	ft_gpa_realloc(void *alloc, t_buffer buf, t_size newsize,
				t_size align);
void		ft_gpa_free(void *allocator, t_buffer buf);
t_buffer	ft_alloc_clone(void *self, t_buffer buffer)\
				__attribute__((__nonnull__(1)));

t_reporta	ft_reporta(void);
void		ft_reporta_destroy(t_reporta *gpa)\
				__attribute__((__nonnull__(1)));
t_buffer	ft_reporta_alloc(void *alloc, t_size size, t_size align)\
				__attribute__((__nonnull__(1)));
t_buffer	ft_reporta_realloc(void *alloc, t_buffer buf, t_size newsize,
				t_size align)\
				__attribute__((__nonnull__(1)));
void		ft_reporta_free(void *allocator, t_buffer buf)\
				__attribute__((__nonnull__(1)));

t_allocator	ft_arena_allocator(t_arena *arena)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	ft_gpa_allocator(t_gpa *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	ft_reporta_allocator(t_reporta *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	ft_new_page_alloc(void)\
				__attribute__((__const__));

#endif
