/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocators.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 16:00:44 by jaicastr          #+#    #+#             */
/*   Updated: 2026/10/03 16:00:47 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATORS_H
# define ALLOCATORS_H

# include "types/allocators_types.h"
# include "alloc/general_allocator.h"
# include "alloc/page_alloc.h"
# include "alloc/report_allocator.h"
# include "alloc/arena_alloc.h"

t_allocator	xft_arena_allocator(t_arena *arena)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_gpa_allocator(t_gpa *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_reporta_allocator(t_reporta *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	xft_page_allocator(void)\
				__attribute__((__const__));

#endif
