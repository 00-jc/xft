/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocators.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaicastr <jaicastr@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 23:39:13 by jaicastr          #+#    #+#             */
/*   Updated: 2026/06/30 11:18:34 by jaicastr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATORS_H
# define ALLOCATORS_H

# include "types/allocators_types.h"
# include "alloc/general_allocator.h"
# include "alloc/page_alloc.h"
# include "alloc/report_allocator.h"
# include "alloc/arena_alloc.h"

t_allocator	ft_arena_allocator(t_arena *arena)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	ft_gpa_allocator(t_gpa *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	ft_reporta_allocator(t_reporta *gpa)\
				__attribute__((__nonnull__(1), __const__));
t_allocator	ft_new_page_alloc(void)\
				__attribute__((__const__));

#endif
