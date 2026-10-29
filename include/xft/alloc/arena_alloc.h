/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOC_H
# define ARENA_ALLOC_H

# include <stddef.h>
# include <xft/primitives.h>
# include <xft/types/arena_types.h>

t_arena				xft_new_arena(void);
t_any				xft_arena_alloc(t_arena *__restrict__ const allocator,
						t_size size, t_size align)\
						__attribute__((__nonnull__(1), __alloc_align__(3)));
void				xft_destroy_arena(t_arena *alloc)\
						__attribute__((__nonnull__(1)));
t_arena_checkpoint	xft_arena_checkpoint(const t_arena *__restrict__ const arena)\
						__attribute__((__nonnull__(1), pure));
void				xft_arena_rewind_clean(t_arena *__restrict__ const arena,
						t_arena_checkpoint checkpoint);
void				xft_arena_rewind(t_arena *__restrict__ const arena,
						t_arena_checkpoint checkpoint);

#endif
