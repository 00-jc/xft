/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_TYPES_H
# define ARENA_TYPES_H

# include <stddef.h>
# include <xft/primitives.h>

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

#endif
