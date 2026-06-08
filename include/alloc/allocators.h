/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocators.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 04:25:08 by username          #+#    #+#             */
/*   Updated: 2026/06/06 04:55:10 by username         ###   ########.fr       */
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
