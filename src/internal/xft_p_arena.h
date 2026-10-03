/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_p_arena.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:01:29 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 18:01:32 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XFT_P_ARENA_H
# define XFT_P_ARENA_H

# include "alloc/arena_alloc.h"
# include "syscalls.h"
# include "mem.h"

t_any				get_next_ptr(t_hugepage *slab, t_size align)\
						__attribute__((__nonnull__(1), __returns_nonnull__));

t_u32a				xft_arena_move_fwd(t_arena *alloc,\
						t_size size, int flags)\
						__attribute__((__nonnull__(1)));

t_hugepage			*new_hugepage(t_hugepage *prev,\
						t_size size, int flags);

void				xft_arena_clean_fwd(const t_arena *alloc)\
						__attribute__((__nonnull__(1)));

t_size				xft_match_paging(t_size page_size)\
						__attribute__((const));

#endif
