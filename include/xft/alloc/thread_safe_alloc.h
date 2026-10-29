/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safe_alloc.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 14:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 14:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_SAFE_ALLOC_H
# define THREAD_SAFE_ALLOC_H

# include <xft/types/allocators_types.h>
# include <xft/types/alloc_types.h>

t_ts_gpa		xft_new_ts_gpa(void);
t_buffer		xft_ts_gpa_alloc(t_any alloc, t_size size, t_size align)\
					__attribute__((__nonnull__(1)));
t_buffer		xft_ts_gpa_realloc(t_any alloc, t_buffer buf, t_size newsize,
					t_size align)\
					__attribute__((__nonnull__(1)));
void			xft_ts_gpa_free(t_any alloc, t_buffer buf)\
					__attribute__((__nonnull__(1)));
void			xft_ts_gpa_destroy(t_any alloc)\
					__attribute__((__nonnull__(1)));

t_ts_reporta	xft_new_ts_reporta(void);
t_buffer		xft_ts_reporta_alloc(t_any alloc, t_size size, t_size align)\
					__attribute__((__nonnull__(1)));
t_buffer		xft_ts_reporta_realloc(t_any alloc, t_buffer buf,
					t_size newsize, t_size align)\
					__attribute__((__nonnull__(1)));
void			xft_ts_reporta_free(t_any alloc, t_buffer buf)\
					__attribute__((__nonnull__(1)));
void			xft_ts_reporta_destroy(t_any alloc)\
					__attribute__((__nonnull__(1)));

t_ts_arena		xft_new_ts_arena(void);
t_buffer		xft_ts_arena_alloc(t_any alloc, t_size size, t_size align)\
					__attribute__((__nonnull__(1)));
t_buffer		xft_ts_arena_realloc(t_any alloc, t_buffer buf, t_size newsize,
					t_size align)\
					__attribute__((__nonnull__(1)));
void			xft_ts_arena_free(t_any alloc, t_buffer buf)\
					__attribute__((__nonnull__(1)));
void			xft_ts_arena_destroy(t_any alloc)\
					__attribute__((__nonnull__(1)));

t_allocator		xft_ts_gpa_allocator(t_ts_gpa *gpa)\
					__attribute__((__nonnull__(1), __const__));
t_allocator		xft_ts_reporta_allocator(t_ts_reporta *gpa)\
					__attribute__((__nonnull__(1), __const__));
t_allocator		xft_ts_arena_allocator(t_ts_arena *arena)\
					__attribute__((__nonnull__(1), __const__));

#endif
