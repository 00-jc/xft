/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 22:35:07 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <syscall.h>
# include <sys/mman.h>
# include "syscalls.h"
# include "mem.h"

typedef struct s_hugepage
{
	struct s_hugepage	*next;
	struct s_hugepage	*prev;
	size_t				page_size;
	size_t				total;
	size_t				used;
	t_u8				data[];
}	t_hugepage;

typedef struct s_arena
{
	t_hugepage		*current;
}	t_arena;

typedef struct s_checkpoint
{
	size_t			used;
	t_hugepage		*location;
}	t_arena_checkpoint;

typedef void	(*t_free)(void *alloc, t_buffer old)\
				__attribute__((__nonnull__(1)));

typedef void	(*t_reallocate)(void *alloc, t_buffer old, size_t new_size)\
				__attribute__((__nonnull__(1)));

typedef void	(*t_allocate)(void *alloc, size_t size, size_t align)\
				__attribute__((__nonnull__(1)));

typedef void	(*t_destroy)(void *alloc)\
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

# define HUGEPAGE_2MB    2097152UL
# define HUGEPAGE_8MB    8388608UL
# define HUGEPAGE_16MB   16777216UL
# define HUGEPAGE_256MB  268435456UL
# define HUGEPAGE_512MB  536870912UL
# define HUGEPAGE_1GB    1073741824UL
# define HUGEPAGE_2GB    2147483648UL
# define HUGEPAGE_16GB   17179869184UL

# ifndef MAP_HUGE_2MB
#  define MAP_HUGE_2MB 0
# endif
# ifndef MAP_HUGE_8MB
#  define MAP_HUGE_8MB 0
# endif
# ifndef MAP_HUGE_16MB
#  define MAP_HUGE_16MB 0
# endif
# ifndef MAP_HUGE_256MB
#  define MAP_HUGE_256MB 0
# endif
# ifndef MAP_HUGE_512MB
#  define MAP_HUGE_512MB 0
# endif
# ifndef MAP_HUGE_1GB
#  define MAP_HUGE_1GB 0
# endif
# ifndef MAP_HUGE_2GB
#  define MAP_HUGE_2GB 0
# endif
# ifndef MAP_HUGE_16GB
#  define MAP_HUGE_16GB 0
# endif

t_arena				ft_new_arena_alloc(void);
void				*ft_arena_alloc(t_arena *__restrict__ const allocator,
						size_t size, size_t align)\
						__attribute__((nonnull(1)));
void				ft_destroy_arena(t_arena *alloc)\
						__attribute__((__nonnull__(1)));
t_arena_checkpoint	ft_arena_checkpoint(const t_arena *__restrict__ const arena)\
						__attribute__((__nonnull__(1),\
						pure));
void				ft_arena_rewind_clean(t_arena *__restrict__ const arena,
						t_arena_checkpoint checkpoint);
void				ft_arena_rewind(t_arena *__restrict__ const arena,
						t_arena_checkpoint checkpoint);
t_buffer			ft_palloc(size_t size);
t_buffer			ft_palloc_resize(t_buffer b, size_t new_size);
void				ft_palloc_free(t_buffer b);

#endif
