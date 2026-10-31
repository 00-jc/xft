/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xft_ts_vtable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 14:00:00 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/29 14:00:00 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <xft/alloc.h>

__attribute__((__nonnull__(1), __const__))
t_allocator	xft_ts_gpa_allocator(t_ts_gpa *gpa)
{
	static t_alloc_vtable const	vtable = {
		.free = xft_ts_gpa_free,
		.realloc = xft_ts_gpa_realloc,
		.allocate = xft_ts_gpa_alloc,
		.destroy = xft_ts_gpa_destroy,
		.clone = xft_alloc_clone,
	};

	return ((t_allocator){
		.vtable = &vtable,
		.allocator = gpa,
	});
}

__attribute__((__nonnull__(1), __const__))
t_allocator	xft_ts_reporta_allocator(t_ts_reporta *gpa)
{
	static t_alloc_vtable const	vtable = {
		.free = xft_ts_reporta_free,
		.realloc = xft_ts_reporta_realloc,
		.allocate = xft_ts_reporta_alloc,
		.destroy = xft_ts_reporta_destroy,
		.clone = xft_alloc_clone,
	};

	return ((t_allocator){
		.vtable = &vtable,
		.allocator = gpa,
	});
}

__attribute__((__nonnull__(1), __const__))
t_allocator	xft_ts_arena_allocator(t_ts_arena *arena)
{
	static t_alloc_vtable const	vtable = {
		.free = xft_ts_arena_free,
		.realloc = xft_ts_arena_realloc,
		.allocate = xft_ts_arena_alloc,
		.destroy = xft_ts_arena_destroy,
		.clone = xft_alloc_clone,
	};

	return ((t_allocator){
		.vtable = &vtable,
		.allocator = arena,
	});
}
