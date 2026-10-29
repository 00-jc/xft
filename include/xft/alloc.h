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

# include <xft/types/allocators_types.h>
# include <xft/types/alloc_types.h>
# include <xft/alloc/thread_safe_alloc.h>

t_gpa		xft_new_gpa(void);
void		xft_gpa_destroy(t_gpa *gpa);
t_buffer	xft_gpa_alloc(t_any alloc, t_size size, t_size align);
t_buffer	xft_gpa_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align);
void		xft_gpa_free(t_any allocator, t_buffer buf);
t_buffer	xft_alloc_clone(t_any self, t_buffer buffer)\
				__attribute__((__nonnull__(1)));

t_reporta	xft_new_reporta(void);
void		xft_reporta_destroy(t_reporta *gpa)\
				__attribute__((__nonnull__(1)));
t_buffer	xft_reporta_alloc(t_any alloc, t_size size, t_size align)\
				__attribute__((__nonnull__(1)));
t_buffer	xft_reporta_realloc(t_any alloc, t_buffer buf, t_size newsize,
				t_size align)\
				__attribute__((__nonnull__(1)));
void		xft_reporta_free(t_any allocator, t_buffer buf)\
				__attribute__((__nonnull__(1)));

t_allocator	xft_arena_allocator(t_arena *arena)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_gpa_allocator(t_gpa *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_reporta_allocator(t_reporta *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_page_allocator(void)\
				__attribute__((__const__));

#endif
