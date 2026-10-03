/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "types/allocators_types.h"
# include "alloc/page_alloc.h"
# include "alloc/arena_alloc.h"

# define GPA_CLASSES 	14ULL
# define GPA_SLABSIZE	131072ULL
# define REPORTA_BUFFER	1024ULL

typedef struct s_gpa
{
	t_any	slab;
	t_size	slabsize;
	t_any	bmp;
	t_any	free[GPA_CLASSES];
}	t_gpa;

typedef struct s_reporta
{
	t_any		slab;
	t_size		slabsize;
	t_any		bmp;
	t_any		free[GPA_CLASSES];
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

t_gpa		xft_new_gpa(void);
void		xft_gpa_destroy(t_gpa *gpa);
t_buffer	xft_gpa_alloc(t_any alloc, t_size size, t_size align);
t_buffer	xft_gpa_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align);
void		xft_gpa_free(t_any allocator, t_buffer buf);
t_buffer	xft_alloc_clone(t_any self, t_buffer buffer)\
				__attribute__((__nonnull__(1)));

t_reporta	xft_new_reporta(void);
void		xft_reporta_destroy(t_reporta *gpa)\
				__attribute__((__nonnull__(1)));
t_buffer	xft_reporta_alloc(t_any alloc, t_size size, t_size align)\
				__attribute__((__nonnull__(1)));
t_buffer	xft_reporta_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align)\
				__attribute__((__nonnull__(1)));
void		xft_reporta_free(t_any allocator, t_buffer buf)\
				__attribute__((__nonnull__(1)));

t_allocator	xft_arena_allocator(t_arena *arena)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_gpa_allocator(t_gpa *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_reporta_allocator(t_reporta *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_page_allocator(void)\
				__attribute__((__const__));

#endif
