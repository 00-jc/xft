/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:14:01 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/15 04:23:13 by jaicastr         ###   ########.fr       */
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

# define HUGEPAGE_2MB    2097152UL
# define HUGEPAGE_4MB    4194304UL
# define HUGEPAGE_16MB   16777216UL
# define HUGEPAGE_256MB  268435456UL
# define HUGEPAGE_512MB  536870912UL
# define HUGEPAGE_1GB    1073741824UL
# define HUGEPAGE_2GB    2147483648UL
# define HUGEPAGE_16GB   17179869184UL

# ifndef MAP_HUGE_2MB
#  define MAP_HUGE_2MB 0
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

# ifndef DEF_ALIGN
#  define DEF_ALIGN 32
# endif

void				*ft_alloc_align(size_t size, size_t align);
void				*ft_alloc(size_t size);
void				ft_free(void **ptr)\
						__attribute__((__nonnull__(1)));
void				ft_free_array(void ***arr)\
						__attribute__((__nonnull__(1)));
void				*ft_calloc(size_t n, size_t size);
void				*ft_extend(void *ptr, size_t n, size_t size);
void				*ft_extend_zero(void *ptr, size_t n, size_t size);
void				*ft_realloc(void *ptr, size_t n, size_t size);
void				*ft_recalloc(void *ptr, size_t n, size_t size);
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

#endif
