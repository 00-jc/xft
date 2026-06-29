/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report_allocator_types.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@mail.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 16:02:57 by username          #+#    #+#             */
/*   Updated: 2026/06/28 16:02:59 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORT_ALLOCATOR_TYPES_H
# define REPORT_ALLOCATOR_TYPES_H

# include "primitives.h"
# include "alloc/basic.h"

typedef struct s_reporta
{
	void	*slab;
	t_size	slabsize;
	void	*bmp;
	void	*free[GPA_CLASSES];
	t_size	n_allocs;
	t_size	n_frees;
	t_size	slabs;
	t_size	reuses;
	t_size	misses;
	t_size	free_depth[GPA_CLASSES];
	t_size	paged;
	t_f64	avg_frag;
}	t_reporta;

#endif
