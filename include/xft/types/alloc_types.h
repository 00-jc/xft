/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 13:43:41 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_TYPES_H
# define ALLOC_TYPES_H

# include <stddef.h>
# include <xft/primitives.h>
# include <xft/mem.h>
# include <xft/types/atomic_types.h>

typedef enum e_hugepage_size : t_u64
{
	HUGEPAGE_2MB = 2097152,
	HUGEPAGE_8MB = 8388608,
	HUGEPAGE_16MB = 16777216,
	HUGEPAGE_256MB = 268435456,
	HUGEPAGE_512MB = 536870912,
	HUGEPAGE_1GB = 1073741824,
	HUGEPAGE_2GB = 2147483648,
	HUGEPAGE_16GB = 17179869184,
}	t_hugepage_size;

// largest tier a t_size can hold
# if UINTPTR_MAX > 0xFFFFFFFF

typedef enum e_hugepage_max : t_u64
{
	HUGEPAGE_MAX = HUGEPAGE_16GB,
}	t_hugepage_max;

# else

typedef enum e_hugepage_max : t_u64
{
	HUGEPAGE_MAX = HUGEPAGE_2GB,
}	t_hugepage_max;

# endif

typedef enum e_gpa_conf : t_u32
{
	GPA_CLASSES = 14,
	GPA_SLABSIZE = 131072,
}	t_gpa_conf;

typedef enum e_reporta_conf : t_u16
{
	REPORTA_BUFFER = 1024,
}	t_reporta_conf;

typedef struct s_allocator	t_allocator;

typedef void		(*t_free)(t_any alloc, t_buffer old)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_reallocate)(t_any alloc, t_buffer old, t_size new_size,\
						t_size align)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_allocate)(t_any alloc, t_size size, t_size align)\
						__attribute__((__nonnull__(1)));

typedef void		(*t_destroy)(t_any alloc)\
						__attribute__((__nonnull__(1)));

typedef t_buffer	(*t_clone)(t_allocator self, t_buffer buffer);

typedef struct e_alloc_vtable
{
	t_free			free;
	t_reallocate	realloc;
	t_allocate		allocate;
	t_destroy		destroy;
	t_clone			clone;
} __attribute__((__aligned__(__GCC_CONSTRUCTIVE_SIZE)))	t_alloc_vtable;

typedef struct s_allocator
{
	_Alignas(__GCC_CONSTRUCTIVE_SIZE)
	const t_alloc_vtable	*__restrict__ vtable;
	t_any					allocator;
}	t_allocator;

typedef struct s_page_alloc
{
	t_u8	_pad;
}	t_page_alloc;

typedef struct s_hugepage
{
	struct s_hugepage	*next;
	struct s_hugepage	*prev;
	t_size				page_size;
	t_size				total;
	t_size				used;
	t_u8				data[];
}	t_hugepage;

typedef struct s_arena
{
	t_hugepage		*current;
}	t_arena;

typedef struct s_checkpoint
{
	t_size			used;
	t_hugepage		*location;
}	t_arena_checkpoint;

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

typedef struct s_ts_gpa
{
	t_mutex		mutex;
	t_gpa		gpa;
}	t_ts_gpa;

typedef struct s_ts_arena
{
	t_mutex		mutex;
	t_arena		arena;
}	t_ts_arena;

typedef struct s_ts_reporta
{
	t_mutex		mutex;
	t_reporta	reporta;
}	t_ts_reporta;

#endif
