/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include <xft/types/alloc_types.h>

t_buffer			xft_palloc(t_size size);
t_buffer			xft_palloc_reserve(t_size size);
t_result			xft_palloc_commit(t_any ptr, t_size size)\
						__attribute__((__nonnull__(1)));
t_result			xft_palloc_guard(t_any ptr, t_size size)\
						__attribute__((__nonnull__(1)));
t_buffer			xft_palloc_resize(t_buffer b, t_size new_size);
void				xft_palloc_free(t_buffer b);

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

t_gpa				xft_new_gpa(void);
void				xft_gpa_destroy(t_gpa *gpa);
t_buffer			xft_gpa_alloc(t_any alloc, t_size size, t_size align);
t_buffer			xft_gpa_realloc(t_any alloc, t_buffer buf, t_size newsize,
						t_size align);
void				xft_gpa_free(t_any allocator, t_buffer buf);
t_buffer			xft_alloc_clone(t_allocator self, t_buffer buffer);

t_reporta			xft_new_reporta(void);
void				xft_reporta_destroy(t_reporta *gpa)\
						__attribute__((__nonnull__(1)));
t_buffer			xft_reporta_alloc(t_any alloc, t_size size, t_size align)\
						__attribute__((__nonnull__(1)));
t_buffer			xft_reporta_realloc(t_any alloc, t_buffer buf,
						t_size newsize, t_size align)\
						__attribute__((__nonnull__(1)));
void				xft_reporta_free(t_any allocator, t_buffer buf)\
						__attribute__((__nonnull__(1)));

t_ts_gpa			xft_new_ts_gpa(void);
t_buffer			xft_ts_gpa_alloc(t_any alloc, t_size size, t_size align)\
						__attribute__((__nonnull__(1)));
t_buffer			xft_ts_gpa_realloc(t_any alloc, t_buffer buf,
						t_size newsize, t_size align)\
						__attribute__((__nonnull__(1)));
void				xft_ts_gpa_free(t_any alloc, t_buffer buf)\
						__attribute__((__nonnull__(1)));
void				xft_ts_gpa_destroy(t_any alloc)\
						__attribute__((__nonnull__(1)));

t_ts_reporta		xft_new_ts_reporta(void);
t_buffer			xft_ts_reporta_alloc(t_any alloc, t_size size, t_size align)\
						__attribute__((__nonnull__(1)));
t_buffer			xft_ts_reporta_realloc(t_any alloc, t_buffer buf,
						t_size newsize, t_size align)\
						__attribute__((__nonnull__(1)));
void				xft_ts_reporta_free(t_any alloc, t_buffer buf)\
						__attribute__((__nonnull__(1)));
void				xft_ts_reporta_destroy(t_any alloc)\
						__attribute__((__nonnull__(1)));

t_ts_arena			xft_new_ts_arena(void);
t_buffer			xft_ts_arena_alloc(t_any alloc, t_size size, t_size align)\
						__attribute__((__nonnull__(1)));
t_buffer			xft_ts_arena_realloc(t_any alloc, t_buffer buf,
						t_size newsize, t_size align)\
						__attribute__((__nonnull__(1)));
void				xft_ts_arena_free(t_any alloc, t_buffer buf)\
						__attribute__((__nonnull__(1)));
void				xft_ts_arena_destroy(t_any alloc)\
						__attribute__((__nonnull__(1)));

t_allocator			xft_arena_allocator(t_arena *arena)\
						__attribute__((__nonnull__(1), __const__));
t_allocator			xft_gpa_allocator(t_gpa *gpa)\
						__attribute__((__nonnull__(1), __const__));
t_allocator			xft_reporta_allocator(t_reporta *gpa)\
						__attribute__((__nonnull__(1), __const__));
t_allocator			xft_page_allocator(void)\
						__attribute__((__const__));
t_allocator			xft_ts_gpa_allocator(t_ts_gpa *gpa)\
						__attribute__((__nonnull__(1), __const__));
t_allocator			xft_ts_reporta_allocator(t_ts_reporta *gpa)\
						__attribute__((__nonnull__(1), __const__));
t_allocator			xft_ts_arena_allocator(t_ts_arena *arena)\
						__attribute__((__nonnull__(1), __const__));

#endif
