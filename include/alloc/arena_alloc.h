/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/05/16 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOC_H
# define ARENA_ALLOC_H

# ifdef __cplusplus

extern "C"
{

# endif

# include <stddef.h>
# include "types.h"

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

t_arena				ft_new_arena_alloc(void);
void				*ft_arena_alloc(t_arena *__restrict__ const allocator,
						size_t size, size_t align)\
						__attribute__((nonnull(1)));
void				ft_destroy_arena(t_arena *alloc)\
						__attribute__((__nonnull__(1)));
t_arena_checkpoint	ft_arena_checkpoint(const t_arena *__restrict__ const arena)\
						__attribute__((__nonnull__(1), pure));
void				ft_arena_rewind_clean(t_arena *__restrict__ const arena,
						t_arena_checkpoint checkpoint);
void				ft_arena_rewind(t_arena *__restrict__ const arena,
						t_arena_checkpoint checkpoint);

# ifdef __cplusplus
}
# endif

#endif
