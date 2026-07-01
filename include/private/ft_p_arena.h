/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_arena.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/29 23:39:19 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_ARENA_H
# define FT_P_ARENA_H

# include "alloc/arena_alloc.h"
# include "syscalls.h"
# include "mem.h"

void				*get_next_ptr(t_hugepage *slab, t_size align)\
						__attribute__((nonnull(1), returns_nonnull));

t_u32a				ft_arena_move_fwd(t_arena *alloc,\
						t_size size, int flags)\
						__attribute__((nonnull(1)));

t_hugepage			*new_hugepage(t_hugepage *prev,\
						t_size size, int flags);

void				ft_arena_clean_fwd(const t_arena *alloc)\
						__attribute__((__nonnull__(1)));

t_size				ft_match_paging(t_size page_size)\
						__attribute__((const));

#endif
