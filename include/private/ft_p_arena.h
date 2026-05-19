/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_arena.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:55:45 by jaicastr          #+#    #+#             */
/*   Updated: 2026/04/16 19:58:44 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_ARENA_H
# define FT_P_ARENA_H

# include "alloc/arena_alloc.h"
# include "syscalls.h"
# include "mem.h"

void				*get_next_ptr(t_hugepage *slab, size_t align)\
						__attribute__((nonnull(1), returns_nonnull));

t_u32a				ft_arena_move_fwd(t_arena *alloc,\
						size_t size, int flags)\
						__attribute__((nonnull(1)));

t_hugepage			*new_hugepage(t_hugepage *prev,\
						size_t size, int flags);

void				ft_arena_clean_fwd(const t_arena *alloc)\
						__attribute__((__nonnull__(1)));

size_t				ft_match_paging(size_t page_size)\
						__attribute__((const));

#endif
