/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc_types.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 00:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/06 00:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOC_TYPES_H
# define ARENA_ALLOC_TYPES_H

# include <stddef.h>
# include "primitives.h"

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

#endif
