/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:12 by jaicastr          #+#    #+#             */
/*   Updated: 2026/07/01 13:41:56 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "types/allocators_types.h"
# include "alloc/page_alloc.h"
# include "alloc/arena_alloc.h"

// GPA

# define GPA_CLASSES 	14ULL
# define GPA_SLABSIZE	131072ULL
# define REPORTA_BUFFER	1024ULL

typedef struct s_gpa
{
	void	*slab;
	t_size	slabsize;
	void	*bmp;
	void	*free[GPA_CLASSES];
}	t_gpa;

typedef struct s_reporta
{
	void		*slab;
	t_size		slabsize;
	void		*bmp;
	void		*free[GPA_CLASSES];
	t_size		n_allocs;
	t_size		n_frees;
	t_size		slabs;
	t_size		reuses;
	t_size		misses;
	t_size		free_depth[GPA_CLASSES];
	t_size		paged;
	t_f64		avg_frag;
	t_u8		buffer[REPORTA_BUFFER];
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
